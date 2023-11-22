/*
** EPITECH PROJECT, 2023
** projet.c
** File description:
** Hugo Dufour
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "setting_up.h"
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int min(int a, int b, int c)
{
    int min = a;

    if (b < min)
        min = b;
    if (c < min)
        min = c;
    return min;
}

long get_file_size(char const *filepath)
{
    struct stat s;

    stat(filepath, &s);
    return s.st_size;
}

void my_putstr(char const *str)
{
    for (int c = 0; str[c] != '\0'; c++)
        write(1, &str[c], 1);
}

process_data init_data(char **board, int num_lines)
{
    process_data d;

    d.max = 0;
    d.max_i = 0;
    d.max_j = 0;
    d.i;
    d.j;
    return d;
}

int handle_error(int file_descriptor, char **arg)
{
    if (file_descriptor == -1) {
        my_putstr("Error: No such file or directory\n");
        return 84;
    }
    if (errno == EISDIR) {
        my_putstr("Error: Is a directory\n");
        return 84;
    }
    if (errno == EACCES) {
        my_putstr("Error: Permission denied\n");
        return 84;
    }
    return 0;
}

int validate_pattern(char *pattern)
{
    int i = 0;

    for (; pattern[i] != '\0'; i++) {
        if (pattern[i] != '.' && pattern[i] != 'o')
            return 84;
    }
    return 0;
}

void print_board(char **board)
{
    for (int i = 0; board[i] != NULL; i++) {
        my_putstr(board[i]);
        my_putstr("\n");
    }
}

int my_strlen(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++);
    return i;
}
