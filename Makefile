LIBS_W = -lglfw3dll -lglew32 -lopengl32 -lm
LIBS_L = -lglfw -lGL -lGLEW -lm

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

mainW: main.o globjects.o objects.o entity.o linkedlist.o program.o
	gcc -o main main.o globjects.o objects.o entity.o linkedlist.o  program.o ${LIBS_W}

mainL: main.o globjects.o objects.o entity.o linkedlist.o program.o
	gcc -o main main.o globjects.o objects.o entity.o linkedlist.o  program.o ${LIBS_L}

clearWindows:
	del *.o

clearLinux:
	@rm *.o

runWindows: mainW clearWindows
	./main.exe

runLinux: mainL clearLinux
	./main