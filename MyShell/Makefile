# Makefile for MyShell
CC = gcc
OPS = -g -W -Wall -O2 -c

all : MyShell

MyShell : main.o showArgv.o proc_cmd.o built_in.o external_cmd.o 
	$(CC) -pthread -o MyShell main.o showArgv.o proc_cmd.o built_in.o external_cmd.o

main.o : main.c main.h const.h
	$(CC) $(OPS) main.c

showArgv.o : showArgv.c showArgv.h
	$(CC) $(OPS) showArgv.c

proc_cmd.o : proc_cmd.c proc_cmd.h const.h
	$(CC) $(OPS) proc_cmd.c

built_in.o : built_in.c built_in.h const.h
	$(CC) $(OPS) built_in.c

external_cmd.o : external_cmd.c external_cmd.h
	$(CC) $(OPS) external_cmd.c

clear : 
	rm -rf *.o MyShell

