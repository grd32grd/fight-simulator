#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "defs.h"

/*
  Function:  main
  Purpose:   the main program which will span a # of threads simulating fights
       in:   # of command line arguments, array containing the command line arguments
   return:   int 0 to signal end of program 
*/
int main(int argc, char *argv[]) {

  //Seeds our random integer generator
  srand( (unsigned)time( NULL ) );

  StatsType* statArray[NUM_SCENARIOS];
  int numRuns;

  //Sets the # of runs to executable to the default if a valid command line argument isn't inputted
  if (!(argc > 1 && sscanf(argv[1], "%d", &numRuns) == 1)){
    numRuns = NUM_RUNS;
  }
  
  //Set up our stat array so have a statType for any # of scenarios we'll have
  setUpStatArray(&statArray);

  //Simulates the runs
  runs(&statArray, numRuns);
  
  //Prints out the stats after all runs have been completed
  printStats(&statArray, numRuns);
  
  //De-allocates all allocated memory in the statTypes
  cleanUpStats(&statArray);

  return 0;
}

/*
  Function:  randm
  Purpose:   returns a pseudo randomly generated number, 
             in the range 0 to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1) 
*/
int randm(int max) {
  double r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) ); 
  return (int)(r * max);
}