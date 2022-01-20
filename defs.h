#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_RUNS       100
#define NUM_PIRATES     10
#define NUM_SCENARIOS    3

#define TORT_STRENGTH    5
#define TORT_ARMOUR      8
#define HARE_STRENGTH    8
#define HARE_ARMOUR      5
#define HERO_HEALTH     20
#define PIRATE_HEALTH   10
#define SWORD_STRENGTH   2

#define MAX_STR         64

//ASK FOR THE PURPOSE OF THIS RESULT TYPE
typedef enum { SUCCESS, FAILURE, PART_SUCCESS, RES_UNKNOWN } ResultType;
typedef enum { FRONT, BACK } DirectionType;

typedef struct {	// Stats for one scenario, accumulated over all runs
  int numSuccess;
  int numPartSuccess;
  int numFailure;
} StatsType;

typedef struct {	// One fighter:  Tortoise, Hare, or Pirate
  int  strength;
  int  armour;
  int  health;
} FighterType;

typedef struct Node {
  FighterType  *data;
  struct Node  *next;
} NodeType;

typedef struct {	// Stores the fighting pirates for one scenario
  NodeType *head;
  NodeType *tail;
} DequeType;

typedef struct {	// Specs for one scenario of one run
  DequeType   *pirates;
  FighterType *tort;
  FighterType *hare;
  StatsType   *stats;
} RunSpecsType;

typedef struct {	// Specs for one fight of one scenario of one run
  FighterType  *hero;
  DequeType    *pirates;
  DirectionType dir;
  sem_t        *dqMutex;
} FightSpecsType;


//MAIN.C
int randm(int);		// Pseudo-random number generator function

//INIT.C
void initPirates(DequeType *pirates);
void initFighter(int s, int a, int h, FighterType **fighter);
void initRunSpec(FighterType *tort, FighterType *hare, DequeType *pirates, StatsType *stats, RunSpecsType **runSpec);
void initFightSpec(FighterType *hero, DequeType *pirates, DirectionType dir, sem_t *mutex, FightSpecsType **fightSpec);
void initStats(int success, int partSuccess, int failure, StatsType **stats);

//SETUP.C
void setUpPirateDeque(DequeType *pirates);
void setUpPirateClones(DequeType *pirates, DequeType *pirateClones);
void setUpStatArray(StatsType **statArray);
void setUpRuns(DequeType *pirateClones, StatsType **statArray, FighterType **torts, FighterType **hares, RunSpecsType **runs);
void setUpScenarios(RunSpecsType** runSpecs, pthread_t* scenarios);

//PIRATES.C
void addPirate(DequeType *pirates, FighterType *pirate);
void removePirateFront(DequeType *pirates, FighterType **pirate);
void removePirateBack(DequeType *pirates, FighterType **pirate);
void copyPirates(DequeType *source, DequeType *dest);
int noPiratesLeft(DequeType *pirates);

//PROCESSES.C
void runs(StatsType **statArray, int numRuns);
void *scenarioThread(void *arg);
void *fightThread(void *arg);
void fight(FighterType *hero, FighterType *pirate);

//HELPER.C
void updateStats(RunSpecsType *runSpec);
void printStats(StatsType **statArray, int numRuns);
void cleanUpPirates(DequeType *deque);
void cleanUpRuns(RunSpecsType **runs);
void cleanUpScenario(FightSpecsType *front, FightSpecsType *back);
void cleanUpStats(StatsType **statArray);

#endif