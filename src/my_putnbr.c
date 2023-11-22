/*
** EPITECH PROJECT, 2023
** projet.c
** File description:
** Hugo Dufour
*/

#include <unistd.h>

static void my_putchar(char c)
{
    write(1, &c, 1);
}

static int handle_negative(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb *= -1;
    }
    return nb;
}

static void print_extrem_number(int negative, char lastChar)
{
    if (negative == 1) {
        my_putchar('-');
    }
    my_putchar('2');
    my_putchar('1');
    my_putchar('4');
    my_putchar('7');
    my_putchar('4');
    my_putchar('8');
    my_putchar('3');
    my_putchar('6');
    my_putchar('4');
    my_putchar(lastChar);
}

static void handle_missing_zeroes(int n)
{
    for (int i = 0; i < n; i++) {
        my_putchar('0');
    }
}

static int reverse(int nb)
{
    int toReturn = 0;

    while (nb != 0) {
        toReturn = toReturn * 10 + nb % 10;
        nb /= 10;
    }
    return toReturn;
}

static int lengthof(int nb)
{
    int i = 0;

    while (nb > 0) {
        nb /= 10;
        i++;
    }
    return i;
}

static int handle_zero(int nb)
{
    if (nb == 0) {
        my_putchar('0');
        return 1;
    }
    return 0;
}

void my_putnbr(int nb)
{
    int missed;
    int number;
    int negative = (nb < 0) ? 1 : 0;
    char lastChar = (nb == -2147483648) ? '8' : '7';

    if (handle_zero(nb) == 1)
        return;
    if (nb == -2147483648 || nb == 2147483647) {
        print_extrem_number(negative, lastChar);
        return;
    }
    nb = handle_negative(nb);
    missed = lengthof(nb) - lengthof(reverse(nb));
    nb = reverse(nb);
    while (nb > 0) {
        number = nb % 10;
        nb /= 10;
        my_putchar(number + '0');
    }
    handle_missing_zeroes(missed);
}
