NAME=jackdump_jackconn
SRC=jackdump_jackconn.c
OBJ=$(SRC:.c=.o)

CFLAGS=-Wall -Werror -g
CC=gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(shell pkg-config --libs jack) -o $@ $^

clean:
	rm -f $(NAME) $(OBJ)
