##
## EPITECH PROJECT, 2023
## setting up
## File description:
## Makefile
##

NAME = setting_up

SRC = main.c utils.c my_putnbr.c setting_up.c my_getnbr.c
OBJ = $(SRC:.c=.o)

CC = gcc

VPATH = src

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	cd src
	rm -f $(OBJ)
	cd ../

fclean: clean
	rm -f $(NAME)

re: fclean all
