 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <locale.h>
#include <ctype.h>

//==============================================================================================

const int New_line = '\n';

//==============================================================================================

struct string // Создали структуру для строк
{
    char* str;
    int len; 
};

struct text // Создали структуру для текста
{
    char* buffer;
    struct string* lines;
    long int n_lines;
    long int size;
};

//==============================================================================================

struct text create_text(FILE* file); //Заполняем структуру текста

long int size_file(FILE* file); //возвращает размер файла для динамической памяти буфера

char* create_buffer(FILE* file, long int* n_lines, long int* size); //Создаём буфер и считаем количество строк в нём

struct string* placing_pointers_in_text(char* buffer, const long int n_lines); //Скопировали в буфер(структуру массив) из файла

int comparator_direct(const void* left, const void* right); //Компаратор по началу строки

int comparator_reverse(const void* left, const void* right); //Компаратор по концу строки

void print_text(FILE* file, struct string* strings, const long int n_lines); //Печать массива техта в файл

void print_buffer(FILE* file, char* buffer, const long int size); // Печать основного текста

void quick_sort(struct string* strings, const long int n_lines, int(*comparator)(const void* , const void* )); //Сортировка массивка qsort

void bubble_sort(struct string* strings, const long int n_lines, int(*comparator) (const void*, const void*)); //Сортировка массива bubble sort

void swap(struct string* left, struct string* right); //Свап элементов для сортировки

void free_memory(struct string* lines, char* buffer); //Освобождение памяти

//============================================================================================

int main(int argc, const char* argv[])
{  
    setlocale(LC_ALL, "ru_RU.cp1251");

    FILE* input = fopen(argv[1], "r"); //Открыли файл на чтение
    assert(input != NULL);

    struct text input_text = create_text(input);

    fclose(input);// Закрыли файл

    qsort(input_text.lines, input_text.n_lines, sizeof(struct string), comparator_direct);  //Отсортировали массив (структуру) по началу

    FILE* output = fopen("Text_sorted.txt", "w");//Открыли файл для записи
    assert(output != NULL);

    fprintf(output, "Direct sorted text\n\n");
    print_text(output, input_text.lines, input_text.n_lines);//Напечатили в файл отсортированный массив
    fclose(output);//Закрыли файл

    quick_sort(input_text.lines, input_text.n_lines, comparator_reverse);
    //qsort(lines, n_lines, sizeof(struct string), comparator_reverse);
    //bubble_sort(lines, n_lines, comparator_reverse);  //Отсортировали массив с конца

    output = fopen("Text_sorted.txt", "a");//Открываем файл для записи
    assert(output != NULL);

    fprintf(output, "\nReverse sotred text\n\n");
    print_text(output, input_text.lines, input_text.n_lines);//Напечатали отсортированный массив по концу
    fclose(output);//Закрыли файл

    output = fopen("Text_sorted.txt", "a");//Открываем файл для записи
    assert(output != NULL);

    fprintf(output, "\nOriginal text\n\n");
    print_buffer(output, input_text.buffer, input_text.size);//Напечатали массив
    fclose(output);//Закрыли файл

    free_memory(input_text.lines, input_text.buffer); //Освобождение памяти

    return 0;
}


//==============================================================

struct text create_text(FILE* file)
{
    assert(file != NULL);

    struct text input_text = {};

    input_text.buffer = create_buffer(file, &input_text.n_lines, &input_text.size);
    input_text.lines = placing_pointers_in_text(input_text.buffer, input_text.n_lines);

    return input_text;
}

long int size_file(FILE* file)
{
    assert(file != NULL);

    struct stat info = {};
    fstat(fileno(file), &info);

    return info.st_size;
}

char* create_buffer(FILE* file, long int* n_lines, long int* size)
{
    assert(file != NULL);
    assert(n_lines != NULL);
    assert(size != NULL);

    *size = size_file(file);

    char* buffer = (char*) calloc(*size, sizeof(char));

    fseek(file, 0, SEEK_SET);
    fread(buffer, sizeof(char), *size, file);

    char* begin_line = buffer;
    char* end_line = buffer;

    long int count = 0;

    while ((end_line = strchr(begin_line, New_line)) != NULL)
    {
        begin_line = end_line + 1;
        count++;
    }

    *n_lines = count;

    return buffer;
}

struct string* placing_pointers_in_text(char* buffer, const long int n_lines) 
{
    assert(buffer != NULL);
    assert(n_lines != 0);

    struct string* strings = (struct string*) calloc(n_lines, sizeof(struct string));

    assert(strings != NULL);

    char* pointer_begin = buffer;
    char* pointer_end = buffer;

    for (int i = 0; i < n_lines ; i++) 
    {
        pointer_end = strchr(pointer_begin, New_line);
    
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
    assert(size != 0);

    fwrite(buffer, sizeof(char), size, file);
}

void print_text(FILE* file, struct string* strings, const long int n_lines)
{
    assert(file != NULL);
    assert(strings != NULL);
    assert(n_lines != 0);

    for (int index_strings = 0; index_strings < n_lines; index_strings++)
    {   
        fwrite((strings + index_strings)->str, sizeof(char), (strings + index_strings)->len, file);
        putc(New_line, file);
    }
}

int comparator_direct(const void* left, const void* right) 
{
    char* left_begin  = (((struct string*) left) ->str);
    char* left_end    = (((struct string*) left) ->str) + (((struct string*)left) ->len);
    char* right_begin = (((struct string*) right)->str);
    char* right_end   = (((struct string*) right)->str) + (((struct string*)right)->len);

    while ((!isalpha(*left_begin))  && (left_begin  != left_end))   ++left_begin;
    while ((!isalpha(*right_begin)) && (right_begin != right_end))  ++right_begin;

    while ((*left_begin == *right_begin) && (left_begin != left_end) && (right_begin != right_end))
    {  
        ++left_begin;
        ++right_begin;

        while ((!isalpha(*left_begin))  && (left_begin  != left_end))  ++left_begin;
        while ((!isalpha(*right_begin)) && (right_begin != right_end)) ++right_begin;      
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
        return ((int)(unsigned char)(*left_begin) - (int)(unsigned char)(*right_begin));
    }
}

int comparator_reverse(const void* left, const void* right)
{
    char* left_begin  = (((struct string*) left) ->str) + (((struct string*) left) ->len) - 1;
    char* left_end    = (((struct string*) left) ->str);
    char* right_begin = (((struct string*) right)->str) + (((struct string*) right)->len) - 1;
    char* right_end   = (((struct string*) right)->str);

    while ((!isalpha(*left_begin))  && (left_begin  != left_end))  --left_begin;
    while ((!isalpha(*right_begin)) && (right_begin != right_end)) --right_begin;

    while ((*left_begin == *right_begin) && (left_begin != left_end) && (right_begin != right_end))
    {   
        --left_begin;
        --right_begin;

        while ((!isalpha(*left_begin))  && (left_begin  != left_end))  --left_begin;
        while ((!isalpha(*right_begin)) && (right_begin != right_end)) --right_begin;
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
        return ((int)(unsigned char)(*left_begin) - (int)(unsigned char)(*right_begin));
    }
}

void swap(struct string* left, struct string* right)
{
    struct string temp = *left;
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
        while (comparator(&strings[index_left],  &selected_element) < 0) ++index_left;
        while (comparator(&strings[index_right], &selected_element) > 0) --index_right;
        
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
            if (comparator(&strings[index_two], &strings[index_two + 1]) > 0)
                {
                    swap(&strings[index_two], &strings[index_two + 1]); 
                }
        }
    }
}