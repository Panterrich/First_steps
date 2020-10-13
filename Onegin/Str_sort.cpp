#include "Onegin.h"

//==============================================================================================

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