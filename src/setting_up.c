/*
** EPITECH PROJECT, 2023
** projet.c
** File description:
** Hugo Dufour
*/

#include "setting_up.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int create_board(char **board, int num_lines, int pattern_length,
    char *pattern)
{
    int next_pattern = 0;

    if (!board)
        return 84;
    for (int i = 0; i < num_lines; i++) {
        board[i] = malloc(sizeof(char) * (num_lines + 1));
        if (!board[i]) {
            return 84;
        }
        for (int j = 0; j < num_lines; j++) {
            board[i][j] = pattern[next_pattern];
            next_pattern = (next_pattern + 1) % pattern_length;
        }
        board[i][num_lines] = '\0';
    }
    board[num_lines] = NULL;
    return 0;
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

static void handle_square(process_data data, char **board, int num_lines,
    int row_length)
{
    if (data.i < num_lines && data.j < row_length)
        board[data.i][data.j] = 'x';
}

int process_board(char **board, int num_lines)
{
    process_data data = init_data(board, num_lines);
    int row_length = my_strlen(board[0]);
    int aux[num_lines][row_length + 1];

    for (int i = 0; i < num_lines; i++)
        for (int j = 0; j < row_length + 1; j++)
            aux[i][j] = 0;
    for (data.i = 0; data.i < num_lines && board[data.i] != NULL; data.i++)
        for (data.j = 0; data.j < row_length && board[data.i][data.j] != '\0';
            data.j++)
            update_aux_and_find_max(&data, aux, board);
    for (data.i = data.max_i; data.i >= 0 && data.i > data.max_i - data.max;
        data.i--)
        for (data.j = data.max_j; data.j >= 0 && data.j > data.max_j -
            data.max;data.j--)
            handle_square(data, board, num_lines, row_length);
    return 0;
}

static char *findFirstLine(char *buffer)
{
    char *firstLine = malloc(sizeof(char) * 100);

    for (int i = 0; buffer[i] != '\n'; i++) {
        firstLine[i] = buffer[i];
    }
    return firstLine;
}

static char **read_board(char *buffer, int size, int numberSize)
{
    char **board = malloc(sizeof(char *) * (size + 1));
    int j = 0;
    int k = 0;
    int ignore = 0;

    board[j] = malloc(sizeof(char) * (numberSize + 1));
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (ignore == 0 && buffer[i] != '\n') {
            continue;
        } else if (ignore == 0 && buffer[i] == '\n') {
            ignore = 1;
            continue;
        }
        if (buffer[i] == '\n') {
            board[j][k] = '\0';
            j++;
            k = 0;
            board[j] = malloc(sizeof(char) * (numberSize + 1));
            continue;
        }
        board[j][k] = buffer[i];
        k++;
    }
    board[size] = NULL;
    return board;
}

static int get_second_line_size(char *buffer)
{
    int i = 0;
    int size = 0;

    for (; buffer[i] != '\n'; i++);
    i++;
    for (; buffer[i] != '\n'; i++)
        size++;
    return size;
}

int process_file(char *file, int file_descriptor)
{
    char **board;
    char *firstLine;
    int secondLineSize;
    int file_size = get_file_size(file);
    char *buffer = malloc(sizeof(char) * (file_size + 1));
    int size;

    if (read(file_descriptor, buffer, file_size) == -1) {
        my_putstr("Error: Read failed\n");
        return 84;
    }
    secondLineSize = get_second_line_size(buffer);
    firstLine = findFirstLine(buffer);
    size = my_getnbr(firstLine);
    board = read_board(buffer, size, secondLineSize);
    if (process_board(board, size) == 84)
        return 84;
    print_board(board);
    return 0;
}

int setting_up_file(char *file)
{
    int fileDescriptor = 0;
    int error = 0;

    fileDescriptor = open(file, O_RDONLY);
    error = handle_error(fileDescriptor, &file);
    if (error == 84)
        return 84;
    return process_file(file, fileDescriptor);
}

int setting_up_params(char *num, char *pattern)
{
    int num_lines = my_getnbr(num);
    int pattern_length = my_strlen(pattern);
    char **board;

    if (num_lines <= 0 || pattern_length == 0 || validate_pattern(pattern) == 84) {
        my_putstr("Error: Invalid parameters\n");
        return 84;
    }
    board = malloc(sizeof(char *) * (num_lines + 1));
    if (create_board(board, num_lines, pattern_length, pattern) == 84) {
        my_putstr("Error: Pattern mismatch\n");
        return 84;
    }
    if (process_board(board, num_lines) == 84)
        return 84;
    print_board(board);
    return 0;
}
