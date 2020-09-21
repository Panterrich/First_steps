#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

#include "Onegin.h"

//==============================================================================================

const int new_line = '\n';

//==============================================================================================

long int size_file(FILE* file) 
{
    assert(file != NULL);

    struct stat info;
    fstat(fileno(file), &info);

    return info.st_size;
}

char* create_buffer(FILE* file, long int* n_lines, long int* size)
{
    assert(file != NULL);
    assert(n_lines != NULL);

    *size = size_file(file);

    char* buffer = (char*) calloc(*size, sizeof(char));

    fseek(file, 0, SEEK_SET);
    fread((char*) buffer, sizeof(char), *size, file);

    char* begin_line = buffer;
    char* end_line;

    while ((end_line = strchr(begin_line, new_line)) != NULL)
    {
        begin_line = end_line + 1;
        (*n_lines)++;
    }

    return buffer;
}

struct string* copy_text(char* buffer, const long int n_lines) 
{

    assert(buffer != NULL);
    assert(n_lines != 0);

    struct string* strings = (struct string*) calloc(n_lines, sizeof(struct string));

    assert(strings != NULL);

    char* pointer_begin = buffer;
    char* pointer_end = buffer;

    for (int i = 0; i < n_lines ; i++) 
    {
        pointer_end = strchr(pointer_begin, new_line);
    
        (strings + i)->str = pointer_begin;
        (strings + i)->len = pointer_end - pointer_begin;

        pointer_begin = pointer_end + 1;
    }

    return strings;
}

void print_buffer(FILE* file, char* buffer, const long int size)
{
    assert(file != NULL);
    assert(buffer != NULL);

    for (int i = 0; i < size; i++) 
    {
        putc(buffer[i], file);
    }
}

void print_text(FILE* file, struct string* strings, char* buffer, const long int n_lines)
{
    assert(file != NULL);
    assert(strings != NULL);
    assert(buffer != NULL);
    assert(n_lines != 0);

    for (int index_strings = 0; index_strings < n_lines; index_strings++)
    {
        for (int index_char = 0; index_char < (strings + index_strings)->len; index_char++)
        {   
            putc(*(((strings + index_strings)->str) + index_char), file);
        }
        putc(new_line, file);
    }
}

int comparator_direct(const void* left, const void* right) 
{
    char* left_begin = (((struct string*)left)->str);
    char* left_end = (((struct string*)left)->str) + (((struct string*)left)->len);
    char* right_begin = (((struct string*)right)->str);
    char* right_end = (((struct string*)right)->str) + (((struct string*)right)->len);

    while ((!isalpha(*left_begin)) && (left_begin != left_end))
        {
            ++left_begin;
        }
    while ((!isalpha(*right_begin)) && (left_begin != left_end))
        {
            ++right_begin;
        }

    while ((*left_begin == *right_begin) && (left_begin != left_end) && (right_begin != right_end))
    {  
        ++left_begin;
        ++right_begin;

        while ((!isalpha(*left_begin)) && (left_begin != left_end))
        {
            ++left_begin;
        }

        while ((!isalpha(*right_begin)) && (right_begin != right_end))
        {
            ++right_begin;
        }
        
    }

    if ((left_begin == left_end) && (right_begin == right_end))
    {
        return 0;
    }
    else if (left_begin == left_end)
    {
        return -1;
    }
    else if (right_begin == right_end)
    {
        return 1;
    }
    else 
    {
        return ((int)(*left_begin) - (int)(*right_begin));
    }
}

int comparator_reverse(const void* left, const void* right)
{
    char* left_begin = (((struct string*)left)->str) + (((struct string*)left)->len) - 1;
    char* left_end = (((struct string*)left)->str) - 1;
    char* right_begin = ((struct string*)right)->str + (((struct string*)right)->len) - 1;
    char* right_end = (((struct string*)right)->str) - 1;

    while ((!isalpha(*left_begin)) && (left_begin != left_end))
        {
            --left_begin;
        }
    while ((!isalpha(*right_begin)) && (left_begin != left_end))
        {
            --right_begin;
        }

    while ((*left_begin == *right_begin) && (left_begin != left_end) && (right_begin != right_end))
    {   
        --left_begin;
        --right_begin;

        while ((!isalpha(*left_begin)) && (left_begin != left_end))
        {
            --left_begin;
        }
        
        while ((!isalpha(*right_begin)) && (right_begin != right_end))
        {
            --right_begin;
        }
    }

    if ((left_begin == left_end) && (right_begin == right_end))
    {
        return 0;
    }
    else if (left_begin == left_end)
    {
        return -1;
    }
    else if (right_begin == right_end)
    {
        return 1;
    }
    else 
    {
        return ((int)(*left_begin) - (int)(*right_begin));
    }
}

void swap(struct string* left, struct string* right)
{
    struct string temp;

    temp = *left;
    *left = *right;
    *right = temp;
}

void quick_sort(struct string* strings, const long int n_lines, int(*comparator)(const void*, const void*))
{    
    int index_left = 0;
    int index_right = n_lines - 1;

    struct string selected_element = strings[n_lines / 2];

    do
    {
        while (comparator(&strings[index_left], &selected_element) < 0)
        { 
            ++index_left;
        }
        while (comparator(&strings[index_right], &selected_element) > 0)
        {
            --index_right;
        }
        if (index_left <= index_right)
        {
        swap(&strings[index_left], &strings[index_right]);
        ++index_left;
        --index_right;
        }
    } while (index_left <= index_right);

    if (index_right > 0)
    {
        quick_sort(strings, index_right + 1, comparator);
    }
    if (index_left < n_lines) 
    {
        quick_sort(&strings[index_left], n_lines - index_left, comparator);
    }
}

void free_memory(struct string* lines, char* buffer)
{
    if (lines != NULL)
    {
        free(lines);
    }
    if (buffer != NULL)
    {
        free(buffer);
    }
}

void bubble_sort(struct string* strings, const long int n_lines, int(*comparator) (const void*, const void*))
{
    for (int index_one = 0; index_one < n_lines - 1; index_one++ )
    {
        for (int index_two = 0; index_two < n_lines - index_one - 1; index_two++)
        {
            if (comparator(&strings[index_two], &strings[index_two+1]) > 0)
                {
                    swap(&strings[index_two], &strings[index_two+1]); 
                }
        }
    }
}