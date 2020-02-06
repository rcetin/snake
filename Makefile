%.o: %.cpp
	g++ -c $< -o $@


OBJS = src/main.o src/snake/snake.o

#CC specifies which compiler we're using
CC = g++

CFLAGS = -Wall \
	-I/usr/include/SDL2

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 \
	-lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = snake

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
