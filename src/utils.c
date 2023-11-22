/*
** EPITECH PROJECT, 2023
** projet.c
** File description:
** Hugo Dufour
*/

#include <unistd.h>

int min(int a, int b, int c)
{
    int min = a;

    if (b < min)
        min = b;
    if (c < min)
        min = c;
    return min;
}

void my_putstr(char const *str)
{
    for (int c = 0; str[c] != '\0'; c++)
        write(1, &str[c], 1);
}

int my_strlen(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++);
    return i;
}
