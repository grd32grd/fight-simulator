#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "defs.h"

/*
  Function:  runs
  Purpose:   simulates a number of runs, said number is passed as a parameter
       in:   # of runs to simulate
   in-out:   array of statTypes
   return:   none
*/
void runs(StatsType** statArray, int numRuns){

  for (int i = 0; i < numRuns; i++){

    FighterType *torts[NUM_SCENARIOS], *hares[NUM_SCENARIOS];
    DequeType pirates, pirateClones[NUM_SCENARIOS];
    RunSpecsType* runSpecs[NUM_SCENARIOS];
    pthread_t** scenarios[NUM_SCENARIOS];

    //Set up initial pirate deque
    setUpPirateDeque(&pirates);

    //Set up a number of pirate deque copies, one of each number of scenarios
    setUpPirateClones(&pirates, &pirateClones);

    //Set up the runSpecs
    setUpRuns(&pirateClones, statArray, &torts, &hares, &runSpecs);

    //Sets up and simulates the scenario threads
    setUpScenarios(&runSpecs,scenarios);

    //De-allocates all allocated run memory
    cleanUpRuns(&runSpecs);
  }
}
  
/*
  Function:  scenarioThread
  Purpose:   thread function that simulates a scenario
   in-out:   runSpecType
   return:   int 0 to signal end of program 
*/
void *scenarioThread(void *arg){

  RunSpecsType *runSpec = (RunSpecsType*) arg;
  FightSpecsType front, *frontPtr = &front, back, *backPtr = &back;
  pthread_t frontThread, backThread;
  sem_t mutex;

  //Setting up the mutex
  if (sem_init(&mutex, 0, 1) < 0) {
    printf("Semaphore initializing ERROR.\n");
    exit(1);
  }

  //Setting up the two fightSpecs (one for each direction)
  initFightSpec(runSpec->tort, runSpec->pirates, FRONT, &mutex, &frontPtr);
  initFightSpec(runSpec->hare, runSpec->pirates, BACK, &mutex, &backPtr);

  //Creating and joining the fight threads
  pthread_create(&frontThread, NULL, fightThread, frontPtr);
  pthread_create(&backThread, NULL, fightThread, backPtr);
  pthread_join(frontThread, NULL);
  pthread_join(backThread, NULL);

  //Updates stats after a fight has been simulated
  updateStats(runSpec);

  //De-allocates all allocated scenario memory
  cleanUpScenario(frontPtr, backPtr);

  return 0;
}

/*
  Function:  fightThread
  Purpose:   thread function that simulates a fight process
   in-out:   fightSpecType
   return:   int 0 to signal end of program 
*/
void *fightThread(void *arg) {

  FightSpecsType* fightSpec = (FightSpecsType*) arg;

  //Loops untill either both heros are dead or all pirates are dead
  while (noPiratesLeft(fightSpec->pirates) != 1){

    int tortStatus = RES_UNKNOWN, hareStatus = RES_UNKNOWN;
    FighterType pirate, *piratePtr = &pirate;


    if (sem_wait(fightSpec->dqMutex) < 0) {
      printf("Semaphore wait ERROR.\n");
      exit(1);
    }
  	
    //Either hero fights pirate from either side
    if (fightSpec->dir == FRONT){
      removePirateFront(fightSpec->pirates, &piratePtr);
    }
    else {
      removePirateBack(fightSpec->pirates, &piratePtr);
    }
    fight(fightSpec->hero, piratePtr);

    //Exit condition if either hero dies
    if (fightSpec->hero->health == 0){
      tortStatus = FAILURE;  		   
    }
    else if (fightSpec->hero->health == 0){
      hareStatus = FAILURE;  		   
    }

    if (sem_post(fightSpec->dqMutex) < 0) {
      printf("Semaphore post ERROR.\n");
      exit(1);
    }

    usleep(2000);

    //Break out of loop if both the tort and hare's health have reached 0
    if (tortStatus == FAILURE && hareStatus == FAILURE){
      break;
    }

  }
  return 0;
}

/*
  Function:  fight
  Purpose:   simulates an individual fight between a hero and pirate
   in-out:   hero, pirate
   return:   none
*/
void fight(FighterType* hero,FighterType* pirate){
  pirate->health = 10;
  int heroDamage, pirateDamage, bonusStrength;
    
  while (1){

    if (hero->health == 0) {
      break;
    }
    
    heroDamage = hero->strength - pirate->armour;
    
    //Decrease pirate health after pirate hit (ensures that pirate health never dips below 0 
    //by taking the min. between heroDamage and the remaining pirate health left)
    pirate->health -= (heroDamage < pirate->health) ? heroDamage : pirate->health;

    if (pirate->health == 0) {
      //Hero get's health boost from victory
      hero->health = (hero->health + 3 < HERO_HEALTH) ? hero->health + 3 : HERO_HEALTH;
      break;
    }
    
    //Since pirates love to fight, their strength is boosted before each hit
    bonusStrength = pirate->strength + randm(pirate->strength-1);
    //Ensures pirate damage won't be below 0 if potential edge case is reached
    pirateDamage = (bonusStrength - hero->armour > 0) ? bonusStrength - hero->armour : 0;

    //Decrease hero health after pirate hit (ensures that hero health never dips below 0 
    //by taking the min. between pirateDamage and the remaining hero health left)
    hero->health -= (pirateDamage < hero->health) ? pirateDamage : hero->health;

  }  
}
