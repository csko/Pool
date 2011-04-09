# Makefile by Panteleakis Ioannis
# mail: pioann@csd.auth.gr

MAINSRC = billiard.cpp
MAINLIB = -lglut

SRC = $(MAINSRC) include/3dstexture.cpp include/3dsloader.cpp include/bitmap.c include/texture.c src/game.cpp src/vector.cpp src/layout.cpp

OBJ = $(SRC:.c=.o)

OPT = -O3
CC = g++ $(OPT) -Wall -Wno-write-strings

# You might have to change GLU to MesaGLU depending on your Mesa version
GLLIBS = $(MAINLIB) -lGL -lGLU
LIBS = $(GLLIBS) -L/usr/X11R6/lib -lX11 -lXi -lm -lpthread

all: billiard

.c.o:
	$(CC) -c $<

billiard: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm -f billiard *.o

