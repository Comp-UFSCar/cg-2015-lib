# makefile for first activity
SRC_DIR = ../../src
INCLUDE_DIR = ../../header
LIBS = -lm -lX11

CC = gcc
CFLAGS = -w -std=c99

all: first_activity

first_activity: first_activity.o base_functions.o line.o
	$(CC) -o first_activity first_activity.o base_functions.o line.o $(LIBS) $(CFLAGS)

base_functions.o: $(SRC_DIR)/base_functions.c $(INCLUDE_DIR)/base_functions.h
	$(CC) -c $(SRC_DIR)/base_functions.c $(LIBS) $(CFLAGS)

line.o: $(SRC_DIR)/line.c $(INCLUDE_DIR)/line.h
	$(CC) -c $(SRC_DIR)/line.c $(LIBS) $(CFLAGS)

clean:
	-rm -f *.o first_activity *~

