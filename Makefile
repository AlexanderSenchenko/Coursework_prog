all:
	gcc -Wall -o main src/*.c
gdb:
	gcc -Wall -g -O0 -o g_test src/*.c && gdb ./g_test
