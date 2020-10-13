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

    FILE* input = fopen(argv[1], "r");

    if (input == NULL)
        {
            printf("File is not found, ERROR");
            abort();
        }

    struct Text input_text = {};
    Create_text(input, &input_text);

    fclose(input);

    qsort(input_text.lines, input_text.n_lines, sizeof(struct String), Comparator_direct);

    FILE* output = fopen("Text_sorted.txt", "w");
    assert(output != NULL);

    fprintf(output, "Direct sorted text\n\n");
    Print_text(output, &input_text);
    fclose(output);

    Quick_sort(input_text.lines, input_text.n_lines, Comparator_reverse);
    //qsort(input_text.lines, input_text.n_lines, sizeof(struct String), Comparator_reverse);
    //bubble_sort(input_text.lines, input_text.n_lines, Comparator_reverse);

    output = fopen("Text_sorted.txt", "a");
    assert(output != NULL);

    fprintf(output, "\nReverse sorted text\n\n");
    Print_text(output, &input_text);

    fprintf(output, "\nOriginal text\n\n");
    Print_buffer(output, &input_text);
    fclose(output);

    Free_memory(&input_text);

    return 0;
}
