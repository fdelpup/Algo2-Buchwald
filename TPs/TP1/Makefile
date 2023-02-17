Make:
	- gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o fixcol *.c
val:
	- valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./fixcol 25 lorem.txt
