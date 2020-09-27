#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>
#include <locale.h>

#include "Onegin.h"

//==============================================================================================

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
