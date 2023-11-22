/*
** EPITECH PROJECT, 2023
** projet.c
** File description:
** Hugo Dufour
*/

#include "setting_up.h"
#include <stdlib.h>

static void print_board(char **board)
{
    for (int i = 0; board[i] != NULL; i++) {
        my_putstr(board[i]);
        my_putstr("\n");
    }
}

static int create_board(char **board, int num_lines, int pattern_length,
    char *pattern)
{
    int next_pattern = 0;

    if (!board)
        return 84;
    for (int i = 0; i < num_lines; i++) {
        board[i] = malloc(sizeof(char) * num_lines + 1);
        if (!board[i]) {
            return 84;
        }
        for (int j = 0; j < num_lines; j++) {
            board[i][j] = pattern[next_pattern];
            next_pattern = (next_pattern + 1) % my_strlen(pattern);
        }
    }
    board[num_lines] = NULL;
    return 0;
}

static process_data init_data(char **board, int num_lines)
{
    process_data d;

    d.max = 0;
    d.max_i = 0;
    d.max_j = 0;
    d.i;
    d.j;
    return d;
}

void update_aux_and_find_max(process_data *data, int aux[][data->max_j + 1],
    char **board)
{
    if (board[data->i][data->j] == 'o' || (data->i == 0 || data->j == 0))
        aux[data->i][data->j] = (board[data->i][data->j] == 'o' ? 0 : 1);
    else
        aux[data->i][data->j] = min(aux[data->i - 1][data->j], aux[data->i]
            [data->j - 1], aux[data->i - 1][data->j - 1]) + 1;
    if (data->max < aux[data->i][data->j]) {
        data->max = aux[data->i][data->j];
        data->max_i = data->i;
        data->max_j = data->j;
    }
}

int process_board(char **board, int num_lines)
{
    process_data data = init_data(board, num_lines);
    int aux[num_lines][my_strlen(board[0])];

    for (data.i = 0; data.i < num_lines; data.i++) {
        for (data.j = 0; data.j < my_strlen(board[0]); data.j++) {
            update_aux_and_find_max(&data, aux, board);
        }
    }
    for (data.i = data.max_i; data.i > data.max_i - data.max; data.i--) {
        for (data.j = data.max_j; data.j > data.max_j - data.max; data.j--) {
            board[data.i][data.j] = 'x';
        }
    }
    return 0;
}

int setting_up_file(char *file)
{
    return 0;
}

int setting_up_params(char *num, char *pattern)
{
    int num_lines = my_getnbr(num);
    int pattern_length = my_strlen(pattern);
    char **board;

    if (num_lines <= 0 || pattern_length == 0) {
        my_putstr("Invalid parameters\n");
        return 84;
    }
    board = malloc(sizeof(char *) * num_lines);
    if (create_board(board, num_lines, pattern_length, pattern) == 84) {
        my_putstr("Invalid parameters\n");
        return 84;
    }
    if (process_board(board, num_lines) == 84)
        return 84;
    print_board(board);
    return 0;
}
