##
## EPITECH PROJECT, 2023
## setting up
## File description:
## Makefile
##

NAME = bsq

SRC = main.c utils.c my_putnbr.c setting_up.c my_getnbr.c
OBJ = $(SRC:.c=.o)

INCLUDE = -I./include

CC = gcc

CFLAGS = $(INCLUDE)

VPATH = src

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
