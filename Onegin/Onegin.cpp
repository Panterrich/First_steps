#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

#include "Onegin.h"

//==============================================================================================

void Create_text(FILE* file, struct Text* input_text)
{
    assert(file != NULL);
    assert(input_text != NULL);

    input_text->buffer = Create_buffer(file, &(input_text->n_lines), &(input_text->size));
    input_text->lines = Placing_pointers_in_text(input_text->buffer, input_text->n_lines);
}

size_t Size_file(FILE* file)
{
    assert(file != NULL);

    struct stat info = {};
    fstat(fileno(file), &info);

    return (size_t)info.st_size;
}

char* Create_buffer(FILE* file, size_t* n_lines, size_t* size)
{
    assert(file != NULL);
    assert(n_lines != NULL);
    assert(size != NULL);

    *size = Size_file(file);

    char* buffer = (char*) calloc(*size, sizeof(char));

    fseek(file, 0, SEEK_SET);
    fread(buffer, sizeof(char), *size, file);

    char* begin_line = buffer;
    char* end_line = buffer;

    size_t count = 0;

    while ((end_line = strchr(begin_line, '\n')) != NULL)
    {
        begin_line = end_line + 1;
        count++;
    }

    *n_lines = count;

    return buffer;
}

struct String* Placing_pointers_in_text(char* buffer, const size_t n_lines) 
{
    assert(buffer != NULL);
    assert(n_lines != 0);

    struct String* strings = (struct String*) calloc(n_lines, sizeof(struct String));

    assert(strings != NULL);

    char* pointer_begin = buffer;
    char* pointer_end = buffer;

    for (int i_line = 0; i_line < n_lines ; i_line++) 
    {
        pointer_end = strchr(pointer_begin, '\n');
    
        (strings + i_line)->str = pointer_begin;
        (strings + i_line)->len = pointer_end - pointer_begin;

        pointer_begin = pointer_end + 1;
    }

    return strings;
}

void Print_buffer(FILE* file, char* buffer, const size_t size)
{
    assert(file != NULL);
    assert(buffer != NULL);
    assert(size != 0);

    fwrite(buffer, sizeof(char), size, file);
}

void Print_text(FILE* file, struct String* strings, const size_t n_lines)
{
    assert(file != NULL);
    assert(strings != NULL);
    assert(n_lines != 0);

    for (int index_strings = 0; index_strings < n_lines; index_strings++)
    {   
        fwrite((strings + index_strings)->str, sizeof(char), (strings + index_strings)->len + 1, file);
    }
}

int Comparator_direct(const void* left, const void* right) 
{
    char* left_begin  = (((struct String*) left) ->str);
    char* left_end    = (((struct String*) left) ->str) + (((struct String*) left) ->len);
    char* right_begin = (((struct String*) right)->str);
    char* right_end   = (((struct String*) right)->str) + (((struct String*) right)->len);

    while ((!isalpha((int)(unsigned char)*left_begin))  && (left_begin  != left_end))   ++left_begin;
    while ((!isalpha((int)(unsigned char)*right_begin)) && (right_begin != right_end))  ++right_begin;

    while (((int)(unsigned char)*left_begin == (int)(unsigned char)*right_begin) && (left_begin != left_end) && (right_begin != right_end))
    {  
        ++left_begin;
        ++right_begin;

        while ((!isalpha((int)(unsigned char)*left_begin))  && (*left_begin  != ' ') && (left_begin  != left_end))  ++left_begin;
        while ((!isalpha((int)(unsigned char)*right_begin)) && (*right_begin != ' ') && (right_begin != right_end)) ++right_begin;      
    }

    return ((int)(unsigned char)(*left_begin) - (int)(unsigned char)(*right_begin));
}

int Comparator_reverse(const void* left, const void* right)
{
    char* left_begin  = (((struct String*) left) ->str) + (((struct String*) left) ->len) - 1;
    char* left_end    = (((struct String*) left) ->str);
    char* right_begin = (((struct String*) right)->str) + (((struct String*) right)->len) - 1;
    char* right_end   = (((struct String*) right)->str);

    while ((!isalpha((int)(unsigned char)*left_begin))  && (left_begin  != left_end))  --left_begin;
    while ((!isalpha((int)(unsigned char)*right_begin)) && (right_begin != right_end)) --right_begin;

    while ((*left_begin == *right_begin) && (left_begin != left_end) && (right_begin != right_end))
    {   
        --left_begin;
        --right_begin;

        while ((!isalpha((int)(unsigned char)*left_begin))  && (*left_begin  != ' ') && (left_begin  != left_end))  --left_begin;
        while ((!isalpha((int)(unsigned char)*right_begin)) && (*right_begin != ' ') && (right_begin != right_end)) --right_begin;
    }

    return ((int)(unsigned char)(*left_begin) - (int)(unsigned char)(*right_begin));
}

void Swap(struct String* left, struct String* right)
{
    struct String temp = *left;
    *left = *right;
    *right = temp;
}

void Quick_sort(struct String* strings, const size_t n_lines, int(*comparator)(const void*, const void*))
{    
    assert(strings != NULL);
    assert(comparator != NULL);

    int index_left = 0;
    int index_right = n_lines - 1;

    struct String selected_element = strings[n_lines / 2];

    do
    {
        while (comparator(&strings[index_left],  &selected_element) < 0) ++index_left;
        while (comparator(&strings[index_right], &selected_element) > 0) --index_right;
        
        if (index_left <= index_right)
        {
            Swap(&strings[index_left], &strings[index_right]);

            ++index_left;
            --index_right;
        }
    } while (index_left <= index_right);

    if (index_right > 0)
    {
        Quick_sort(strings, index_right + 1, comparator);
    }

    if (index_left < n_lines) 
    {
        Quick_sort(&strings[index_left], n_lines - index_left, comparator);
    }
}

void Free_memory(struct Text* text)
{
    free(text->lines);
    free(text->buffer);
    
    text->lines = NULL;
    text->buffer = NULL;
}

void Bubble_sort(struct String* strings, const size_t n_lines, int(*comparator) (const void*, const void*))
{
    for (int index_one = 0; index_one < n_lines - 1; index_one++ )
    {
        for (int index_two = 0; index_two < n_lines - index_one - 1; index_two++)
        {
            if (comparator(&strings[index_two], &strings[index_two + 1]) > 0)
                {
                    Swap(&strings[index_two], &strings[index_two + 1]); 
                }
        }
    }
}