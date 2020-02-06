CC = g++
OBJS = src/main.o src/snake/snake.o
CFLAGS = -Wall

LINKER_FLAGS = -lSDL2 \
	-lSDL2_image

OBJ_NAME = snake

%.o: %.cpp
	g++ -c $< -o $@

all : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
