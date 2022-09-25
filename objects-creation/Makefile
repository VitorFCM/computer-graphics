LIBS = -lglfw -lGL -lGLEW -lm

globjects.o: ../globjects.c
	gcc -o globjects.o -c ../globjects.c

objects.o: ../objects.c
	gcc -o objects.o -c ../objects.c

auxiliary.o: auxiliary.c
	gcc -o auxiliary.o -c auxiliary.c

file-manager.o: file-manager.c
	gcc -o file-manager.o -c file-manager.c

triangle-creation.o: triangle-creation.c
	gcc -o triangle-creation.o -c triangle-creation.c

create-obj.o: create-obj.c
	gcc -o create-obj.o -c create-obj.c

create-obj: create-obj.o triangle-creation.o file-manager.o objects.o globjects.o auxiliary.o
	gcc -o create-obj create-obj.o triangle-creation.o file-manager.o objects.o globjects.o auxiliary.o ${LIBS}

clear:
	@rm *.o

run: create-obj clear
	./create-obj

