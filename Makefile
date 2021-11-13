CIBLES = link start
OPTIONS = -Wall -Wextra -std=c11
OBJS = cesar.o main.o
FICHIERS = cesar.c main.c cesar.h
	
link: $(OBJS)
	gcc -o cesar $(OPTIONS) $(OBJS) 

all: $(CIBLES)

build: $(FICHIERS)
	gcc -c cesar.c 
	gcc -c main.c

start:
	bats check.bats

.PHONY: make clean

clean: 	
	rm cesar	
	rm $(OBJS)


