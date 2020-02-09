CC = g++
OBJS = src/main.o \
	 src/snake/snake.o \
	 src/texture/texture.o \
	 src/snake/food.o \
	 src/menu/menu.o

CFLAGS = -Wall \
	-std=c++11

LINKER_FLAGS = -lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf

OBJ_NAME = snake

%.o: %.cpp
	g++ -c $< -o $@

all : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME) $(OBJS)