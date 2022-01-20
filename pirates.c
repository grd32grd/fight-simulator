#include "defs.h"

/*
  Function:  addPirate
  Purpose:   adds the given pirate to the back of the given deque of pirates
       in:   pirate
   in-out:   pirate deque
   return:   none
*/
void addPirate(DequeType* pirates, FighterType* pirate){
    
    NodeType *currNode = pirates->tail;
    NodeType *newNode = malloc(sizeof(NodeType));
    newNode->data = pirate;
    newNode->next = NULL;

    //Sets pirate to be the head on top of it being the tail IF this is the first pirate being added
    if (pirates->head == NULL){ 
        pirates->head = newNode;
    }  

    //Positions new pirate to be at the very end and establishes it as the new tail
    if (pirates->tail != NULL){
        currNode->next = newNode;
    }
    pirates->tail = newNode;
}

/*
  Function:  removePirateFront
  Purpose:   removes the head of the pirate deque and returns it with the out parameter
   in-out:   pirate deque
      out:   pirate
   return:   none
*/
void removePirateFront(DequeType* pirates, FighterType **pirate){
    //Grabs pirate head
    *pirate = pirates->head->data;

    //Sets new head to the following pirate
    pirates->head = pirates->head->next;
}

/*
  Function:  removePirateBack
  Purpose:   removes the tail of the pirate deque and returns it with the out parameter
   in-out:   pirate deque
      out:   pirate
   return:   none
*/
void removePirateBack(DequeType* pirates, FighterType **pirate){
    //Grabs pirate tail
    *pirate = pirates->tail->data;

    NodeType *currNode = pirates->head;
    NodeType *prevNode = NULL;

    while (currNode != NULL){

        //If we've reached the second last pirate, we set it to be the new tail
        if (currNode->next == pirates->tail){
            pirates->tail = currNode;
            pirates->tail->next = NULL;
            break;
            
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
}

/*
  Function:  copyPirates
  Purpose:   takes given source pirate deque and performs a deep copy onto the destination one
       in:   source deque
      out:   destination deque
   return:   none
*/
void copyPirates(DequeType* source, DequeType* dest){
    NodeType *currNode = source->head, *prevNode = NULL;

    //Initalizes new destination deque
    initPirates(dest);

    //Deep copy process, destination deque copies all of the source deque's pirates
    while (currNode != NULL){
        addPirate(dest,currNode->data);
        prevNode = currNode;
        currNode = currNode->next;
    }
}

/*
  Function:  noPiratesLeft
  Purpose:   determines if pirate deque passed on is empty or not
       in:   deque of pirates
   return:   true (1) or false (0) value
*/
int noPiratesLeft(DequeType* pirates){
    return pirates->head == NULL || pirates->tail == NULL;
}