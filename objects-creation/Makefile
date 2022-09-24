LIBS = -lglfw -lGL -lGLEW -lm

globjects.o: ../globjects.c
	gcc -o globjects.o -c ../globjects.c

objects.o: ../objects.c
	gcc -o objects.o -c ../objects.c

triangle-creation.o: triangle-creation.c
	gcc -o triangle-creation.o -c triangle-creation.c

create-obj.o: create-obj.c
	gcc -o create-obj.o -c create-obj.c

create-obj: create-obj.o triangle-creation.o objects.o globjects.o
	gcc -o create-obj create-obj.o triangle-creation.o objects.o globjects.o ${LIBS}

clear:
	@rm *.o

run: create-obj clear
	./create-obj

