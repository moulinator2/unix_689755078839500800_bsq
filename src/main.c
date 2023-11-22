/*
** EPITECH PROJECT, 2023
** projet.c
** File description:
** Hugo Dufour
*/

#include "setting_up.h"

int main(int ac, char **av)
{
    if (ac <= 1 || ac > 3) {
        return 84;
    }
    if (ac == 2)
        return setting_up_file(av[1]);
    else
        return setting_up_params(av[1], av[2]);
}
