LIBS = -lglfw -lGL -lGLEW -lm

globjects.o: globjects.c
	gcc -o globjects.o -c globjects.c

main.o: main.c
	gcc -o main.o -c main.c

main: main.o globjects.o
	gcc -o main main.o globjects.o ${LIBS}

run: main
	./main

clear:
	@rm *.o