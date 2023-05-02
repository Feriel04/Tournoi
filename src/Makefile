CC = gcc
EXEC = tournoi

all = $(EXEC)

LIB = -lm -pthread -lrt

$(EXEC) : main.o alloc_init.o in_out.o utility.o simulation.o
	$(CC) -o $(EXEC) main.o alloc_init.o in_out.o utility.o simulation.o $(LIB)

main.o : main.c
	$(CC) -o main.o -c main.c $(LIB)

alloc_init.o : alloc_init.c
	$(CC) -o alloc_init.o -c alloc_init.c $(LIB)

in_out.o : in_out.c
	$(CC) -o in_out.o -c in_out.c $(LIB)

utility.o : utility.c
	$(CC) -o utility.o -c utility.c $(LIB)

simulation.o : simulation.c
	$(CC) -o simulation.o -c simulation.c $(LIB)

doc:
	doxygen doxyfile

.PHONY: doc
