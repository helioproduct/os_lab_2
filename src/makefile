# FLAGS = -std=c11 -pedantic -Wall -Werror

all: child run

run: main.c
	gcc $(FLAGS) main.c -o run

child: child.c
	gcc $(FLAGS) child.c -o child

clean:
	rm -f *.out run child *.o
