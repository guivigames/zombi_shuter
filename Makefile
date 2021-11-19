CC = g++
CFLAGS = -g -Wall
SRCS = TextureManager.cpp CreateHorde.cpp Bullet.cpp Pickup.cpp character.cpp Zombie.cpp ZombiArena.cpp CreateBackground.cpp
PROG = ZombiArena

SFML = `pkg-config sfml-all --cflags --libs`
LIBS = $(SFML)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)