#include <string.h>
#include <system.h>
#include "mpx_supt.h"
#include <core/serial.h>
#include "memoryblocks.h"
#include "print.h"

memoryList free = {0,NULL,NULL};
memoryList allocated = {0,NULL,NULL};

void initialize_heap(int size)
{

}

void allocate_memory(int bytes)
{

}

void free_memory(int address) // Will, trying to wrap head around it, decent start, need initialize function to visualize
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

      // Check if blocks of free memory need merged
      // if address adjacent in heap contains CMCB of same type (free==0, allocated==1), merge blocks
      // nextCMCB = CMCB, remove a CMCB and LCMB
      // size: sizeof(both blocks of memory) + 2*sizeof(CMCB) + 2*sizeof(LCMB) ---->>>> sizeof(both blocks of memory) + sizeof(CMCB) + sizeof(LCMB)

      break;
    }
    tempAllocated = tempAllocated->nextCMCB;
  }
}
