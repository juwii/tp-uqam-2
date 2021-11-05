CIBLES = build start
OPTIONS = -Wall -Wextra -std=c11
OBJS = cesar.o main.o
FILES = cesar.c main.c cesar.h

all: $(CIBLES)
	
build: $(OBJS)
	gcc -o cesar $(OPTIONS) $(OBJS) 

link: $(FILES)
	gcc -c cesar.c 
	gcc -c main.c

html: 	
	pandoc -c github-pandoc.css -s README.md -o README.html 	

start:
	bats check.bats

.PHONY: clean

clean: 	
	rm cesar	
	rm $(OBJS)


