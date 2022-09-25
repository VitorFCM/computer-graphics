LIBS = -lglfw -lGL -lGLEW -lm

linkedlist.o: ../linkedlist.c
	gcc -o linkedlist.o -c ../linkedlist.c

program.o: ../program.c
	gcc -o program.o -c ../program.c

entity.o: ../entity.c
	gcc -o entity.o -c ../entity.c

globjects.o: ../globjects.c
	gcc -o globjects.o -c ../globjects.c

objects.o: ../objects.c
	gcc -o objects.o -c ../objects.c

auxiliary.o: auxiliary.c
	gcc -o auxiliary.o -c auxiliary.c

file-manager.o: file-manager.c
	gcc -o file-manager.o -c file-manager.c

primitives-creation.o: primitives-creation.c
	gcc -o primitives-creation.o -c primitives-creation.c

create-obj.o: create-obj.c
	gcc -o create-obj.o -c create-obj.c

create-obj: create-obj.o primitives-creation.o file-manager.o objects.o globjects.o auxiliary.o entity.o program.o linkedlist.o
	gcc -o create-obj create-obj.o primitives-creation.o file-manager.o objects.o globjects.o auxiliary.o entity.o program.o linkedlist.o ${LIBS}

clear:
	@rm *.o

run: create-obj clear
	./create-obj

