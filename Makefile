CC = g++
CFLAGS = -g -Wall
SRCS = TextureManager.cpp character.cpp zombi_shuter.cpp framework.cpp
PROG = zombi_shuter

SFML = `pkg-config sfml-all --cflags --libs`
LIBS = $(SFML)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)