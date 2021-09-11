main: main.c fileManager.c
	gcc -Wextra -g -o main main.c fileManager.c -I. -lm
