LIBS = -lglfw3dll -lglew32 -lopengl32 -lm

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

main: main.o globjects.o objects.o entity.o linkedlist.o
	gcc -o main main.o globjects.o objects.o entity.o linkedlist.o ${LIBS}

clearWindows:
	del *.o
clearLinux:
	@rm *.o

runWindows: main clearWindows
	./main.exe
runLinux: main clearLinux
	./main