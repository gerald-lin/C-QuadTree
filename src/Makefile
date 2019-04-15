CC = gcc
CFLAGS = -Wall -ansi -Wfatal-errors
OBJ = main.o quadtree.o image.o fichier.o quadtreeMelange.o gestionClic.o jeu.o menu.o
LDFLAGS = -lMLV

Quadtree: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	./Quadtree
	make mrproper



main.o: main.c jeu.h

quadtree.o: quadtree.c quadtree.h gestionClic.h

image.o: image.c image.h quadtree.h gestionClic.h

fichier.o: fichier.c fichier.h quadtree.h

quadtreeMelange.o: quadtreeMelange.c quadtreeMelange.h quadtree.h fichier.h

gestionClic.o: gestionClic.c gestionClic.h

jeu.o: jeu.c jeu.h quadtree.h image.h fichier.h quadtreeMelange.h gestionClic.h menu.h

menu.o: menu.c menu.h gestionClic.h fichier.h


%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f *.gch

mrproper: clean
	rm -f Quadtree