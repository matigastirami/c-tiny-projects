run:
	gcc -Wall -Wextra -O2 ./src/main.c ./matrix/*.c -o main \
	-I ./matrix \
	&& ./main
