# makefile for activity
SRC_DIR = ../../src
INCLUDE_DIR = ../../header
LIBS = -lm -lX11

CC = gcc
CFLAGS = -w -std=c99

ACTIVITY = example
BASE = base_functions
LIB2D = object2d_functions

all: $(ACTIVITY)

$(ACTIVITY): $(ACTIVITY).o $(BASE).o $(LIB2D).o
	$(CC) -o $(ACTIVITY) $(ACTIVITY).o $(BASE).o $(LIB2D).o $(LIBS) $(CFLAGS)

$(BASE).o: $(SRC_DIR)/$(BASE).c $(INCLUDE_DIR)/$(BASE).h
	$(CC) -c $(SRC_DIR)/$(BASE).c $(LIBS) $(CFLAGS)

$(LIB2D).o: $(SRC_DIR)/$(LIB2D).c $(INCLUDE_DIR)/$(LIB2D).h
	$(CC) -c $(SRC_DIR)/$(LIB2D).c $(LIBS) $(CFLAGS)

clean:
	-rm -f *.o $(ACTIVITY) *~

