build: cesar.c 	
	gcc -o cesar -Wall -Wextra -std=c11 cesar.c 
	
link: 	
	#pandoc -c github-pandoc.css -s README.md -o README.html 	
	#pandoc -s sujet.md -c github-pandoc.css -o sujet.html 

clean: 	
	#rm *.html & rm cesar 
	
start: 	
	#bats check.bats


