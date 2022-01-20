#include <pthread.h>
#include "defs.h"

/*
  Function:  setUpStatArray
  Purpose:   Creates a # of statTypes corresponding to the # of scenarios we'll have
      out:   array containing the statTypes
   return:   none
*/
void setUpStatArray(StatsType **statArray){
  for (int i = 0; i < NUM_SCENARIOS; i++){
    initStats(0, 0, 0, &statArray[i]);
  }
}

/*
  Function:  setUpPirateDeque
  Purpose:   Generates a deque of pirates each with randomized values
      out:   deque containing the pirates
   return:   none
*/
void setUpPirateDeque(DequeType *pirates){
  initPirates(pirates);

  for (int i = 0; i < NUM_PIRATES; i++){
    FighterType pirate, *piratePtr = &pirate;

    int strength = 5 + randm(5);
    int armour = 1 + randm(4);
    int health = PIRATE_HEALTH;
    
    initFighter(strength, armour, health, &piratePtr);
    addPirate(pirates, piratePtr);
  }
}

/*
  Function:  setUpPirateClones
  Purpose:   Sets up multiple pirate deques eqiuvalent to the original pirate deque passed in
       in:   deque containing the original group of pirates
      out:   array containing the clones of pirates
   return:   none
*/
void setUpPirateClones(DequeType *pirates, DequeType *pirateClones){
  for (int i =0; i < NUM_SCENARIOS; i++){
    initPirates(&pirateClones[i]);
    copyPirates(pirates, &pirateClones[i]);
  }      
}

/*
  Function:  setUpRuns
  Purpose:   Sets up a # of runSpec types, all with the help of the in parameters passed onto the function
       in:   deque of pirate clones, array of StatTypes, array of torts, array of hares
      out:   array containing the runSpec types
   return:   none
*/
void setUpRuns(DequeType *pirateClones, StatsType **statArray, FighterType **torts, FighterType **hares, RunSpecsType **runs){
    for (int i = 0; i < NUM_SCENARIOS; i++){

      //Determines which hero (if any) will recieve the sword boost
      int tortBonus = 0, hareBonus = 0;
      if (i == 0){
        tortBonus += SWORD_STRENGTH;
      }
      else if (i == 1){
        hareBonus += SWORD_STRENGTH;
      }

      initFighter(TORT_STRENGTH + tortBonus, TORT_ARMOUR, HERO_HEALTH, &torts[i]);
      initFighter(HARE_STRENGTH + hareBonus, HARE_ARMOUR, HERO_HEALTH, &hares[i]);

      initRunSpec(torts[i], hares[i], &pirateClones[i], statArray[i], &runs[i]);
    }
}

/*
  Function:  setUpScenarios
  Purpose:   Takes in the corresponding runSpecType to create and join scenario threads
       in:   array of runSpecTypes
      out:   array of scenario pthread_t types
   return:   none
*/
void setUpScenarios(RunSpecsType** runSpecs, pthread_t* scenarios){
  
  //Creates a thread
  for (int i = 0; i < NUM_SCENARIOS; i++){
    pthread_create(&scenarios[i], NULL, scenarioThread, runSpecs[i]);
  }
  //Joins the corresponding thread
  for (int i = 0; i < NUM_SCENARIOS; i++){
    pthread_join(scenarios[i],NULL);
  }
  
}