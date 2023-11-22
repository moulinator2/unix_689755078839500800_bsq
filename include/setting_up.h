/*
** EPITECH PROJECT, 2023
** setting_up
** File description:
** setting_up.h
*/

#ifndef SETTING_UP_H_
    #define SETTING_UP_H_

typedef struct process_data {
    int max;
    int max_i;
    int max_j;
    int i;
    int j;
} process_data;

void print_board(char **board);
int setting_up_file(char *file);
int validate_pattern(char *pattern);
long get_file_size(char const *filepath);
int process_board(char **board, int num_lines);
int setting_up_params(char *num, char *pattern);
int handle_error(int file_descriptor, char **arg);
int create_board(char **board, int num_lines, int pattern_length,
    char *pattern);
process_data init_data(char **board, int num_lines);

void my_putstr(char const *str);
int my_strlen(char const *str);
void my_putnbr(int nb);
int my_getnbr(char const *str);
int min(int a, int b, int c);

#endif
