# Nome do projeto
PROJ_NAME = projeto

# Arquivos .c
C_SOURCE = $(wildcard *.c)

# Arquivos .h
H_SOURCE = $(wildcard *.h)

# Arquivos .o
OBJS = $(C_SOURCE:.c=.o)

# Compilador
CC = gcc

RUN := $(PROJ_NAME)
CLEAR = @rm *.o $(PROJ_NAME)

# Flags para o compilador
CC_FLAGS :=
ifeq ($(OS),Windows_NT)
	CC_FLAGS += -lglfw3dll -lglew32 -lopengl32 -lm
	RUN := $(RUN).exe
	CLEAR = del *.o $(PROJ_NAME).exe
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CC_FLAGS += -lglfw -lGL -lGLEW -lm
	endif
endif

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJS)
	$(CC) -o $@ $^ $(CC_FLAGS)

%.o: %.c %.h
	$(CC) -o $@ -c $<

run: $(PROJ_NAME)
	./$(RUN)
	
clear:
	$(CLEAR)
