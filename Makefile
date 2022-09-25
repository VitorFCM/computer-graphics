LIBS_W = -lglfw3dll -lglew32 -lopengl32 -lm
LIBS_L = -lglfw -lGL -lGLEW -lm

auxiliary.o: objects-creation/auxiliary.c
	gcc -o auxiliary.o -c objects-creation/auxiliary.c

file-manager.o: objects-creation/file-manager.c
	gcc -o file-manager.o -c objects-creation/file-manager.c

program.o: program.c
	gcc -o program.o -c program.c

linkedlist.o: linkedlist.c
	gcc -o linkedlist.o -c linkedlist.c

entity.o: entity.c
	gcc -o entity.o -c entity.c

objects.o: objects.c
	gcc -o objects.o -c objects.c

globjects.o: globjects.c
	gcc -o globjects.o -c globjects.c

main.o: main.c
	gcc -o main.o -c main.c

mainW: main.o globjects.o objects.o entity.o linkedlist.o program.o file-manager.o auxiliary.o
	gcc -o main main.o globjects.o objects.o entity.o linkedlist.o  program.o file-manager.o auxiliary.o ${LIBS_W}

mainL: main.o globjects.o objects.o entity.o linkedlist.o program.o file-manager.o auxiliary.o
	gcc -o main main.o globjects.o objects.o entity.o linkedlist.o  program.o file-manager.o auxiliary.o ${LIBS_L}

clearWindows:
	del *.o

clearLinux:
	@rm *.o

runWindows: mainW clearWindows
	./main.exe

runLinux: mainL clearLinux
	./main
