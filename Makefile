LIBS = -lglfw -lGL -lGLEW -lm

main.o: main.c
	gcc -o main.o -c main.c

main: main.o
	gcc -o main main.o ${LIBS}

run: main
	./main

clear:
	@rm *.o