LIBS = -lglfw -lGL -lGLEW -lm

objects.o: objects.c
	gcc -o objects.o -c objects.c

globjects.o: globjects.c
	gcc -o globjects.o -c globjects.c

main.o: main.c
	gcc -o main.o -c main.c

main: main.o globjects.o objects.o
	gcc -o main main.o globjects.o objects.o ${LIBS}

clear:
	@rm *.o

run: main clear
	./main

