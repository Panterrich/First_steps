#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//==============================================================================================

const int new_line = '\n';

//==============================================================================================

struct string // Создали структуру для строк
{
    char* str;
    int len; 
};

//==============================================================================================

FILE* open_file(const char* name, const char* type); //Открыли файл и проверка файла

void close_file(FILE* file_for_closing); //Закрыли файл и проверка закрытия

long int counter_lines(FILE* file); //Подсчитали строки в файле

void copy_text(FILE* file, struct string* strings, char* buffer, const long int n_lines,  const long int size); //Скопировали в буфер(структуру массив) из файла

int comparator_direct(const void* left, const void* right); //Компаратор по началу строки

int comparator_reverse(const void* left, const void* right); //Компаратор по концу строки

void print_text(FILE* file, struct string* strings, char* buffer, const long int n_lines); //Печать массива техта в файл

void print_buffer(FILE* file, char* buffer, const long int size); // Печать основного текста

void quick_sort(struct string* strings, int start, int end, int(*comparator)(const void* , const void* )); //Сортировка массивка с конца

long int size_file(char* name); //возвращает размер файла для динамической памяти буфера

int is_letter(const char c); //Это буква?

void swap(struct string* left, struct string* right); //Свап элементов для сортировки

//============================================================================================

int main()
{  
    FILE* input;
    FILE* output;

    input = open_file("Hamlet.txt", "r"); //Открыли файл для чтения и проверка файла
     
    long int n_lines = 0;
     
    n_lines = counter_lines(input); //Подсчитали строки в файле

    close_file(input);// Закрыли файл

    long int size_of_text = 0;

    size_of_text = size_file("Hamlet.txt");

    char* Buffer = (char*) calloc(size_of_text, sizeof(char));
    struct string* lines = (struct string*) calloc(n_lines, sizeof(struct string));

    input = open_file("Hamlet.txt", "r");//Открыли файл и проверка файла
    copy_text(input, lines, Buffer, n_lines, size_of_text);//Скопировали в буфер(структуру массив) из файла
    close_file(input);//Закрыли файл
     
    qsort(lines, n_lines, sizeof(struct string), comparator_direct);  //Отсортировали массив (структуру) по началу

    output = open_file("Hamlet_sorted.txt", "w");//Открыли файл для записи
    fprintf(output, "Sorted Hamlet text\n\n");
    print_text(output, lines, Buffer, n_lines);//Напечатили в файл отсортированный массив
    close_file(output);//Закрыли файл

    qsort(lines, n_lines, sizeof(struct string), comparator_reverse);
    //quick_sort(lines, 0, n_lines - 1, comparator_direct);//sort_text_reverse();//Отсортировали массив с конца

    output = open_file("Hamlet_sorted.txt", "a");//Открываем файл для записи
    fprintf(output, "\nReverse sotred Hamlet text\n\n");
    print_text(output, lines, Buffer, n_lines);//Напечатали отсортированный массив по концу
    close_file(output);//Закрыли файл

    input = open_file("Hamlet.txt", "r");//Открыли файл и проверка файла
    copy_text(input, lines, Buffer, n_lines, size_of_text);//Скопировали в буфер(структуру массив) из файла
    close_file(input);//Закрыли файл

    output = open_file("Hamlet_sorted.txt", "a");//Открываем файл для записи
    fprintf(output, "\nOriginal Hamlet text\n\n");
    print_buffer(output, Buffer, size_of_text);//Напечатали массив
    close_file(output);//Закрыли файл

    if (lines != NULL)    //Освобождение памяти
    {
        free(lines);
    }
    if (Buffer != NULL)
    {
        free(Buffer);
    }
}

//==============================================================

FILE* open_file(const char* name, const char* type)
{   
    assert(name != NULL);
    assert(type != NULL);

    FILE* file;

    file = fopen(name, type);

    assert(file != NULL);

    if (file = NULL) 
    {    
        printf("%s can't be opened, errror\n", name);
    }

}

void close_file(FILE* file_for_closing) 
{   
    assert(file_for_closing != NULL);

    if (fclose(file_for_closing)) {
    
        printf("File can't be closed, error");
    }
}

long int counter_lines(FILE* file)
{   
    assert(file != NULL);

    int c, count = 0;

    while((c = getc(file)) != EOF) 
    {
        if (c == new_line) 
        { 
            count++;
        }   
    }

    return count;
}

long int size_file(char* name) 
{
    assert(name != NULL);

    FILE* file;

    file = open_file(name, "rb");

    fseek(file, 0, SEEK_END);
    long int size = ftell(file);

    close_file(file);

    return size;
}

void copy_text(FILE* file, struct string* strings, char* buffer, const long int n_lines, const long int size) 
{
    assert(file != NULL);
    assert(strings != NULL);
    assert(buffer != NULL);
    assert(n_lines != 0);
    assert(size != 0);

    fseek(file, 0, SEEK_SET);
    fread((char*) buffer, sizeof(char), size, file);

    fseek(file, 0, SEEK_SET);

    char* pointer_begin = buffer;
    char* pointer_end = buffer;

    for (int i = 0; i < n_lines ; i++) 
    {
        pointer_end = strchr(pointer_begin, new_line);
    
        (strings + i)->str = pointer_begin;
        (strings + i)->len = pointer_end - pointer_begin;

        pointer_begin = pointer_end + 1;
    }
}

void print_buffer(FILE* file, char* buffer, const long int size)
{
    assert(file != NULL);
    assert(buffer != NULL);
    assert(size != 0);

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

    while ((!is_letter(*left_begin)) && (left_begin != left_end))
        {
            left_begin++;
        }
    while ((!is_letter(*right_begin)) && (left_begin != left_end))
        {
            right_begin++;
        }

    while ((*left_begin == *right_begin) && (left_begin != left_end) && (right_begin != right_end))
    {   
        while ((!is_letter(*left_begin)) && (left_begin != left_end))
        {
            left_begin++;
        }

        while ((!is_letter(*right_begin)) && (right_begin != right_end));
        {
            right_begin++;
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

    while ((!is_letter(*left_begin)) && (left_begin != left_end))
        {
            left_begin--;
        }
    while ((!is_letter(*right_begin)) && (left_begin != left_end))
        {
            right_begin--;
        }

    while ((*left_begin == *right_begin) && (left_begin != left_end) && (right_begin != right_end))
    {   
        do
        {
            left_begin--;
        } while ((!is_letter(*left_begin)) && (left_begin != left_end));
        
        do
        {
            right_begin--;
        } while ((!is_letter(*right_begin)) && (right_begin != right_end));
        
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

int is_letter(const char c)
{
    if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

void swap(struct string* left, struct string* right)
{
    struct string* temp;
    temp = left;
    left = right;
    right = temp;

}

void quick_sort(struct string* strings, int start, int end, int(*comparator)(const void*, const void*))
{    
    struct string selected_element = strings[(start + end) / 2];

    int index_left = start;
    int index_right = end;

    while (index_left <= index_right)
    {
        while (comparator(&strings[index_left], &selected_element)>0)
        {
            index_left++;
            printf("1\n");
        }
        while (comparator(&strings[index_right], &selected_element)<0)
        {
            index_right--;
            printf("2\n");
        }
        if (index_left <= index_right)
        {
        printf("3\n");
        swap(&strings[index_left], &strings[index_right]);
        index_left++;
        index_right--;
        }
    }

    if (start < index_right)
    {
        quick_sort(strings, start, index_right, comparator);
    }
    if (index_left > end) 
    {
        quick_sort(strings, index_left, end, comparator);
    }
}