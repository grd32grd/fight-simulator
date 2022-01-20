OPT = -Wall -pthread
OBJ = main.o init.o setup.o pirates.o processes.o helper.o

game:	$(OBJ)
	gcc $(OPT) -o game $(OBJ)

main.o:			main.c defs.h
	gcc $(OPT) -c main.c

init.o:			init.c defs.h
	gcc $(OPT) -c init.c

setup.o:		setup.c defs.h
	gcc $(OPT) -c setup.c

pirates.o:		pirates.c defs.h
	gcc $(OPT) -c pirates.c

processes.o:	processes.c defs.h
	gcc $(OPT) -c processes.c

helper.o:		helper.c defs.h
	gcc $(OPT) -c helper.c

clean:
	rm -f $(OBJ) game