# Printf

Наивная реализация функции <stdio.h> printf () как часть учебной программы 21.
Компиляция статической библиотеки ft_printf
Чтобы использовать эту функцию ft_printf, либо скачайте zip, либо git clone репозиторий и запустите make в корне каталога проекта. Это создаст статическую библиотеку, которую вы можете включить в свою программу.
Компиляция со статической библиотекой ft_printf
Запустив make и made libftprintf.a, вы можете использовать эту функцию со своими программами, добавив #include "ft_printf.h" в файл .h или непосредственно в файлы проекта.
При компиляции не забудьте связать библиотеку libftprintf.a. Пример:
gcc -I включает -o my_program my_file.c my_other_file.c -L. -lftprintf
Тогда просто запустите свою программу!
Полезные ресурсы
Вот некоторые ресурсы, которые я лично нашел очень полезными для этого проекта! Удачи, если вы также решите это!
http://www.cplusplus.com/reference/cstdio/printf/
https://wpollock.com/CPlus/PrintfRef.htm
http://en.cppreference.com/w/c/variadic
https://en.wikipedia.org/wiki/Double-precision_floating-point_format
https://en.wikipedia.org/wiki/UTF-8