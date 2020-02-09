CC = g++
OBJS = src/main.o \
	 src/snake/snake.o \
	 src/texture/texture.o \
	 src/snake/food.o \
	 src/menu/menu.o

CFLAGS = -Wall \
	-std=c++11 \
	-ggdb -O0 -g3

LINKER_FLAGS = -lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf

OBJ_NAME = snake

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

all : $(OBJS)
	$(CC) $(CFLAGS) -o $(OBJ_NAME) $(OBJS) $(LINKER_FLAGS)

clean:
	rm $(OBJ_NAME) $(OBJS)