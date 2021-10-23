build: cesar.o main.o
	gcc -o cesar -Wall -Wextra -std=c11 cesar.o main.o 

link: cesar.c main.c cesar.h
	gcc -c cesar.c 
	gcc -c main.c
html: 	
	#pandoc -c github-pandoc.css -s README.md -o README.html 	
	#pandoc -s sujet.md -c github-pandoc.css -o sujet.html 

clean: 	
	#rm *.html & rm cesar 
	
start: 	
	#bats check.bats


