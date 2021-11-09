#include <string.h>
#include <system.h>
#include "mpx_supt.h"
#include <core/serial.h>
#include "memoryblocks.h"
#include "print.h"

// Move these to Initialize Heap
memoryList free_list = {0,NULL,NULL};
memoryList allocated_list = {0,NULL,NULL};
uint32 start_of_memory;

uint32 initialize_heap(uint32 size){
  start_of_memory = kmalloc(size + sizeof(CMCB));

  CMCB *top = (CMCB*)start_of_memory;
  // create the initial CMCB
  top->beginningAddress = start_of_memory + sizeof(CMCB);
  top->size = size;
  top->type = 0; // is free memory

  // put the first cmcb into the free list.
  free_list.head = top;
  free_list.tail = top;
  free_list.count = 1;
  return 0;
}

void allocate_memory(uint32 bytes)
{
  //if nothing in allocated list:
  // need to declare a cmcb and put it in allocated_list
  // top->beginningAddress? += intbytes + sizeof(cmcb)
  // i think top needs to be global to that effect
  //else
  //add it in and move top->beginninng adress the same way
  //add the shit to allocated_list, were putting it at the end but it can easily go at the front

  //there is 0 error checking here, if there isnt size it'll break
  // but it should work if there is room within free, error checking is for when it works
  CMCB* allocation;
  allocation->size = bytes;
  allocation->type = 1;

  if(allocated_list->count == 0){
  allocated_list->head = allocation;
  allocated_list->tail = allocation;
  allocation->beginningAddress = top->beginningAddress;
  top->beginningAddress +=  (bytes + sizeof(CMCB));

}else{
  allocated_list->tail = allocation;
  allocated_list->head->previousCMCB = allocation;
  allocation->beginningAddress = top->beginningAddress;
  top->beginningAddress +=  (bytes + sizeof(CMCB));

  }
}

void free_memory(int address) // Will, trying to wrap head around it, decent start, need initialize function to visualize.
{
  CMCB* tempAllocated = allocated_list.head;
  while (tempAllocated != NULL)
  {
    if (tempAllocated->beginningAddress == address)
    {
      // Allocate to free list
      allocate_memory(tempAllocated->size);
      // Remove from allocated list
      if(tempAllocated == allocated_list->head){
        allocated_list->head = tempAllocated->nextCMCB;
      }
      //else if it is at the tail,
      else if(tempAllocated == allocated_list->tail){
        allocated_list->tail = tempAllocated->previousCMCB;
        allocated_list->tail->nextCMCB = NULL;
      }
      else{
        tempAllocated->previousCMCB->nextCMCB = tempAllocated->nextCMCB;
        tempAllocated->nextCMCB->previousCMCB = tempAllocated->previousCMCB;
      }
      tempAllocated->nextCMCB = NULL;
      tempAllocated->previousCMCB = NULL;
      allocated_list->count--;
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
  return allocated_list->count == 0;
}

void Show_Allocated_Memory(){
if(allocated_list->count = 0){
  println("Allocated memory is empty ");
}else{
  CMCB* tempCMBC = allocated_list->head;

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
  CMCB* tempCMBC = free_list->head;

    while(tempCMBC != NULL){
          //I dont think i can print things like this but for now fuckit
          //Both are ints, might have to create the string to int method
          //unless we have it and im dumb
          println(tempCMBC->beginningAddress);
          println(tempCMBC->size);
          tempCMBC->nextCMCB;
        }

}
