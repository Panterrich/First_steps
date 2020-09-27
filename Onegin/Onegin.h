#include <stdio.h>

//==============================================================================================

struct string
{
    char* str;
    int len; 
};

struct text
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