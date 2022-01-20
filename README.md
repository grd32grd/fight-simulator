## Purpose
Program written in C that simulates multiple random executions of a battle between two heros facing a pirate crew.

## Source Files
main.c
init.c
setup.c
pirates.c
processes.c
helper.c

## Header Files
defs.h

## Compilation Instructions
Enter the following below in the command line to start up the compiling/linking process.
make

## Launching Instructions
Enter the following below in the command line to execute the program. './game' is our executable, and 'n' represent the number of executions we want. 
By default, 100 executions will be ran if no valid argument is inputted.
./game n

## Program Instructions
Below is a visual representation of the stat summary you'll see after running the program.

Number of Runs: n
+----------------------------------------------------------+
| Hero with sword |  % success  |  % partial  |  %failure  |
+----------------------------------------------------------+
|   Tortoise      |       x     |      x      |       x    |
+----------------------------------------------------------+
|   Hare          |       x     |      x      |       x    |
+----------------------------------------------------------+
|   None          |       x     |      x      |       x    |
+----------------------------------------------------------+