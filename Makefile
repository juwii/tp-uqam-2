<<<<<<< HEAD
build: cesar.c 	
	gcc -o cesar -Wall -Wextra -std=c11 cesar.c 
	
link: 	
	#pandoc -c github-pandoc.css -s README.md -o README.html 	
	#pandoc -s sujet.md -c github-pandoc.css -o sujet.html 

clean: 	
	#rm *.html & rm cesar 
	
start: 	
	#bats check.bats
=======
CIBLES = clean build start
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
	pandoc -s sujet.md -c github-pandoc.css -o sujet.html 

start:
	bats check.bats

.PHONY: clean

clean: 	
	rm cesar	
	rm $(OBJS)
>>>>>>> dev


