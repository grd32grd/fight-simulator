#include "defs.h"

/*
  Function:  initPirates
  Purpose:   Initializes a deque of pirates
      out:   pirate deque
   return:   none
*/
void initPirates(DequeType* pirates){
    
    pirates->head = NULL;
    pirates->tail = NULL;
    
}

/*
  Function:  initFighter
  Purpose:   Initializes a fighter
       in:   strength, armour, health
      out:   the fighter
   return:   none
*/
void initFighter(int s, int a, int h, FighterType **fighter){
    
    FighterType *ptr = malloc(sizeof(FighterType));

    ptr->strength = s;
    ptr->armour = a;
    ptr->health = h;
    *fighter = ptr;
}

/*
  Function:  initRunSpec
  Purpose:   Initializes a runSpecType
       in:   tort, hare, deque of pirates, statType
      out:   the runSpecType
   return:   none
*/
void initRunSpec(FighterType *tort, FighterType *hare, DequeType *pirates, StatsType *stats, RunSpecsType **runSpec){
    
    RunSpecsType *ptr = malloc(sizeof(RunSpecsType));

    ptr->pirates = pirates;
    ptr->tort = tort;
    ptr->hare = hare;
    ptr->stats = stats;
    *runSpec = ptr;

}

/*
  Function:  initFightSpec
  Purpose:   Initializes a fightSpecType
       in:   hero, deque of pirates, direction, mutex
      out:   the fightSpecType
   return:   none
*/
void initFightSpec(FighterType *hero, DequeType *pirates, DirectionType dir, sem_t *mutex, FightSpecsType **fightSpec){

    FightSpecsType *ptr = malloc(sizeof(FightSpecsType));

    ptr->hero = hero;
    ptr->pirates = pirates;
    ptr->dir = dir;
    ptr->dqMutex = mutex;
    *fightSpec = ptr;
}

/*
  Function:  initStats
  Purpose:   Initializes a statsType
       in:   # of successes, partSuccesses, failures
      out:   the statsType
   return:   none
*/
void initStats(int success, int partSuccess, int failure, StatsType **stats){

    StatsType *ptr = malloc(sizeof(StatsType));
    
    ptr->numSuccess = success;
    ptr->numPartSuccess = partSuccess;
    ptr->numFailure = failure;
    *stats = ptr;
}