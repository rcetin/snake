CC = g++
OBJS = src/main.o src/snake/snake.o src/texture/texture.o
CFLAGS = -Wall \
	-std=c++11

LINKER_FLAGS = -lSDL2 \
	-lSDL2_image

OBJ_NAME = snake

%.o: %.cpp
	g++ -c $< -o $@

all : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
