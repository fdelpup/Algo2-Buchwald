Make:
	- gcc -g -Wall -Wconversion -Wtype-limits -pedantic -Werror -o pruebas *.c 
val:
	- valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas 06_usuarios < 06_in > salida.txt

