ONEGIN

This program sorts the strings at the beginning and the end.

The program supports Russian and English. The Russian text must be in cp1251 encoding.

Compile program:

1) In terminal:

        g++ Str_lib.cpp Str_sort.cpp main.c -o app
        ./app "Name_of_file"   
  
Example: 

    ./app "Onegin.txt" 
    ./app "Hamlet.txt"
         
2) Your sorted text is in "Text_sorted.txt"
