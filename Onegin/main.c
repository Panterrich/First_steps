#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

#include "Onegin.h"

//==============================================================================================

int main()
{  
    FILE* input;
    FILE* output;

    input = fopen("Hamlet.txt", "r"); //Открыли файл на чтение

    long int n_lines = 0; //Количество строк
    long int size_of_text = 0; //Размер файла(текста)

    char* buffer = create_buffer(input, &n_lines, &size_of_text); //Создали и заполнили буфер

    struct string* lines = copy_text(buffer, n_lines); //Создали и заполнили массив структур строк

    fclose(input);// Закрыли файл
     
    qsort(lines, n_lines, sizeof(struct string), comparator_direct);  //Отсортировали массив (структуру) по началу

    output = fopen("Hamlet_sorted.txt", "w");//Открыли файл для записи
    fprintf(output, "Sorted Hamlet text\n\n");
    print_text(output, lines, buffer, n_lines);//Напечатили в файл отсортированный массив
    fclose(output);//Закрыли файл

    quick_sort(lines, n_lines, comparator_reverse);
    //qsort(lines, n_lines, sizeof(struct string), comparator_reverse);
    //bubble_sort(lines, n_lines, comparator_reverse);  //Отсортировали массив с конца

    output = fopen("Hamlet_sorted.txt", "a");//Открываем файл для записи
    fprintf(output, "\nReverse sotred Hamlet text\n\n");
    print_text(output, lines, buffer, n_lines);//Напечатали отсортированный массив по концу
    fclose(output);//Закрыли файл

    output = fopen("Hamlet_sorted.txt", "a");//Открываем файл для записи
    fprintf(output, "\nOriginal Hamlet text\n\n");
    print_buffer(output, buffer, size_of_text);//Напечатали массив
    fclose(output);//Закрыли файл

    free_memory(lines, buffer); //Освобождение памяти

    return 0;
}