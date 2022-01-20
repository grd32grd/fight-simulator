#include "defs.h"

/*
  Function:  updateStats
  Purpose:   takes in a runSpecType, computes and updates it's status depending on the heros' healths
   in-out:   runSpec
   return:   none
*/
void updateStats(RunSpecsType* runSpec){

  if (runSpec->tort->health == 0 && runSpec->hare->health == 0){
    runSpec->stats->numFailure += 1;
  }
  else if (runSpec->tort->health == 0 || runSpec->hare->health == 0){
    runSpec->stats->numPartSuccess += 1;

  }
  else if (runSpec->tort->health > 0 && runSpec->hare->health > 0) {
    runSpec->stats->numSuccess += 1;
  }

}

/*
  Function:  printStats
  Purpose:   prints out the results store in the collection of statTypes
      in:    statType array, number of rus
   return:   none
*/
void printStats(StatsType** statArray, int numRuns){

  char hero_str[NUM_SCENARIOS][9] = {"Tortoise", "Hare", "None"};
  char border[59];
  memset(border, '-', 59);
  border[58] = '\0';

  printf("\nNumber of Runs: %d\n", numRuns);
  printf("+%s+\n",border);
  printf("| Hero with sword |  %% success  |  %% partial  |  %%failure  |\n");
  for (int i = 0; i < NUM_SCENARIOS; i++){

    float success = (float) statArray[i]->numSuccess/numRuns * 100;
    float partial = (float) statArray[i]->numPartSuccess/numRuns * 100;
    float failure = (float) statArray[i]->numFailure/numRuns * 100;

    printf("+%s+\n",border);
    printf("|   %-9s     |     %3.0f     |     %3.0f     |     %3.0f    |\n", hero_str[i], success, partial, failure);
  }
  printf("+%s+\n\n",border);

}

/*
  Function:  cleanUpPirates
  Purpose:   de-allocates all allocated memory in given pirate deque
   in-out:   pirate deque
   return:   none
*/
void cleanUpPirates(DequeType* deque){

    NodeType *currNode = deque->head, *prevNode = NULL;
    while (currNode != NULL){
        free(currNode->data);
        prevNode = currNode;
        currNode = currNode->next;
        free(prevNode);
    }

}

/*
  Function:  cleanUpRuns
  Purpose:   de-allocates all allocated memory in given array of RunSpecTypes
   in-out:   array of runSpecTypes variables
   return:   none
*/
void cleanUpRuns(RunSpecsType** runs){

  for (int i = 0; i < NUM_SCENARIOS; i++){
    free(runs[i]->tort);
    free(runs[i]->hare);
    free(runs[i]);
  }

}

/*
  Function:  cleanUpScenario
  Purpose:   de-allocates all allocated memory in a scenario
   in-out:   two fightSpecType variables (one for each direction it represents)
   return:   none
*/
void cleanUpScenario(FightSpecsType* front, FightSpecsType* back){

  free(front);
  free(back);
  
}

/*
  Function:  cleanUpStats
  Purpose:   de-allocates all allocated memory in given array of statTypes
   in-out:   array of statType variables
   return:   none
*/
void cleanUpStats(StatsType** statArray){

  for (int i = 0; i < NUM_SCENARIOS; i++){
    free(statArray[i]);
  }

}