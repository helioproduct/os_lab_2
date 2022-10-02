CC = gcc
FLAGS = -std=c99 -pthread -w -pipe -O3 -Wextra -Werror -Wall -Wno-sign-compare -pedantic -lm

all: run

run: main.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -f *.out run *.o