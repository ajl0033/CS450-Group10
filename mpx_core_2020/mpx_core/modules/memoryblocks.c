#include <string.h>
#include <system.h>
#include "mpx_supt.h"
#include <core/serial.h>
#include "memoryblocks.h"
#include "print.h"

// Move these to Initialize Heap
memoryList free = {0,NULL,NULL};
memoryList allocated = {0,NULL,NULL};

void initialize_heap(int size)
{

}

void allocate_memory(int bytes)
{

}

void free_memory(int address) // Will, trying to wrap head around it, decent start, need initialize function to visualize.
{
  CMCB* tempAllocated = allocated.head;
  while (tempAllocated != NULL)
  {
    if (tempAllocated->beginningAddress == address)
    {
      // Allocate to free list
      allocate_memory(tempAllocated->size);
      // Remove from allocated list
      if(tempAllocated == allocated->head){
        allocated->head = tempAllocated->nextCMCB;
      }
      //else if it is at the tail,
      else if(tempAllocated == allocated->tail){
        allocated->tail = tempAllocated->previousCMCB;
        allocated->tail->nextCMCB = NULL;
      }
      else{
        tempAllocated->previousCMCB->nextCMCB = tempAllocated->nextCMCB;
        tempAllocated->nextCMCB->previousCMCB = tempAllocated->previousCMCB;
      }
      tempAllocated->nextCMCB = NULL;
      tempAllocated->previousCMCB = NULL;
      allocated->count--;
      // Free sizeof(block) + sizeof(CMCB) + sizeof(LCMB)
      // How the heck do i read addresses?!!! Is the Heap a list?

      // Check if blocks of free memory need merged
      // if address adjacent in heap contains CMCB of same type (free==0, allocated==1), merge blocks
      // nextCMCB = CMCB, remove a CMCB and LCMB
      // size: sizeof(both blocks of memory) + 2*sizeof(CMCB) + 2*sizeof(LCMB) ---->>>> sizeof(both blocks of memory) + sizeof(CMCB) + sizeof(LCMB)

      break;
    }
    tempAllocated = tempAllocated->nextCMCB;
  }
}

//0 = false ----- 1 = true
int IsEmpty(){
int IsItEmpty;
isItEmpty = allocated->count;
if(isItEmpty = 0){
  return 0
}
return 1;
}

void Show_Allocated_Memory(){

if(allocated->count = 0){
  println("Allocated memory is empty ");
}else{
  CMCB* tempCMBC = allocated->head;

    while(tempCMBC != NULL){
          //I dont think i can print things like this but for now fuckit
          //Both are ints, might have to create the string to int method
          //unless we have it and im dumb
          println(tempCMBC->beginningAddress);
          println(tempCMBC->size);
          tempCMBC->nextCMCB;
        }
    }
}

void Show_Free_Memory(){

  CMCB* tempCMBC = free->head;

    while(tempCMBC != NULL){
          //I dont think i can print things like this but for now fuckit
          //Both are ints, might have to create the string to int method
          //unless we have it and im dumb
          println(tempCMBC->beginningAddress);
          println(tempCMBC->size);
          tempCMBC->nextCMCB;
        }

}
