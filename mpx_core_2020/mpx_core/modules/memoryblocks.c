#include <string.h>
#include <system.h>
#include "mpx_supt.h"
#include <core/serial.h>
#include "memoryblocks.h"
#include <mem/heap.h>
#include "print.h"

// Move these to Initialize Heap
memoryList free_list = {0,NULL,NULL};
memoryList allocated_list = {0,NULL,NULL};
u32int start_of_memory;
u32int total_size;

u32int initialize_heap(u32int size){
  start_of_memory = kmalloc(size + sizeof(CMCB));
  total_size = size;
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

u32int allocate_memory(u32int bytes)
{
char str[10];
  //could hard code it in each timemp; but lets see if this works
  CMCB* top = free_list.head;

  //error checking for size should go below but idk how
  while(top != NULL){
    if ((start_of_memory + total_size - top->beginningAddress) < (bytes + sizeof(CMCB))) {
      println("\nUNABLE TO ALLOCATE MEMORY");
      return NULL;
    }
    toString(str,(top->size));
    println(str);
    if((u32int) top->size >= (u32int) bytes + sizeof(CMCB)) {
      break;
    }
    top = top->nextCMCB;

  }

CMCB* newFree = (CMCB*) (top->beginningAddress + bytes);
//i think the line below needs some work
newFree->type = 0;
newFree->beginningAddress = top->beginningAddress + bytes + sizeof(CMCB);
newFree->size = top->size - bytes - sizeof(CMCB);

top->type = 1;
top->size = bytes;

if (free_list.head == top) {
  free_list.head = top->nextCMCB;
}
else if (free_list.tail == top) {
  free_list.tail = top->previousCMCB;
}
else {
  top->previousCMCB->nextCMCB = top->nextCMCB;
  top->nextCMCB->previousCMCB = top->previousCMCB;
}

insertCMCB(&free_list, newFree);
insertCMCB(&allocated_list, top);

return top->beginningAddress;
}


int free_memory(void* addressP) // Will
{
  u32int address = (u32int)addressP;
  CMCB* tempAllocated = allocated_list.head;
  while (tempAllocated != NULL)
  {
    if (tempAllocated->beginningAddress == address)
    {
      // Allocate to free list
      // Remove from allocated list
      // Head
      if(tempAllocated == allocated_list.head){
        allocated_list.head = tempAllocated->nextCMCB;
      }
      //else if it is at the tail,
      else if(tempAllocated == allocated_list.tail){
        allocated_list.tail = tempAllocated->previousCMCB;
        allocated_list.tail->nextCMCB = NULL;
      }
      else{
        tempAllocated->previousCMCB->nextCMCB = tempAllocated->nextCMCB;
        tempAllocated->nextCMCB->previousCMCB = tempAllocated->previousCMCB;
      }
      tempAllocated->nextCMCB = NULL;
      tempAllocated->previousCMCB = NULL;
      insertCMCB(&free_list, tempAllocated);
      allocated_list.count--;
      // Free sizeof(block) + sizeof(CMCB) + sizeof(LCMB)
      break;
    }
    tempAllocated = tempAllocated->nextCMCB;
  }

  // Check if blocks of free memory are adjacent and need merged

  CMCB* tempFree = free_list.head;
  CMCB* tempFreeNext = tempFree->nextCMCB;
  while (tempFreeNext != NULL)
  {
      if ((tempFree->beginningAddress + tempFree->size + sizeof(CMCB)) == (tempFreeNext->beginningAddress)) // Check if adjacent blocks are both free
    {
      tempFree->size = tempFree->size + tempFreeNext->size;
      // Remove adjacent from free free_list once blocks of memory are combined
      // Head
      if(tempFreeNext == free_list.head){
        free_list.head = tempFreeNext->nextCMCB;
      }
      //else if it is at the tail,
      else if(tempFreeNext == free_list.tail){
        free_list.tail = tempFreeNext->previousCMCB;
        free_list.tail->nextCMCB = NULL;
      }
      else{
        tempFreeNext->previousCMCB->nextCMCB = tempFreeNext->nextCMCB;
        tempFreeNext->nextCMCB->previousCMCB = tempFreeNext->previousCMCB;
      }
      tempFreeNext->nextCMCB = NULL;
      tempFreeNext->previousCMCB = NULL;
      free_list.count--;
      break;
      }
      tempFreeNext = tempFreeNext->nextCMCB;
      tempFree = tempFree->nextCMCB;
  }
  return 1;
}

//0 = false ----- 1 = true
int IsEmpty(){
  if (allocated_list.count == 0) {
    // set to 1 for empty
    println("\nEMPTY");
    return 1;
  } else {
    println("\nNOT EMPTY");
    return 0;
  }
}

void Show_Allocated_Memory(){
if(allocated_list.count == 0){
  println("Allocated memory is empty ");
}else{
  CMCB* tempCMCB = allocated_list.head;
  char str[10];
    while(tempCMCB != NULL){
          //I dont think i can print things like this but for now
          //Both are ints, might have to create the int to string method

            //println(tempCMCB->beginningAddress);
            //println(tempCMCB->size);
          println(" ");
           toString(str,(tempCMCB->beginningAddress));
           println(str);
           toString(str,(tempCMCB->size));
           println(str);
           println(" ");
          tempCMCB = tempCMCB->nextCMCB;
        }
    }
}

void Show_Free_Memory(){
  CMCB* tempCMCB = free_list.head;
  char str[10];
    while(tempCMCB != NULL){
          //I dont think i can print things like this but for now
          //Both are ints, might have to create the int to string method

            //println(tempCMCB->beginningAddress);
            //println(tempCMCB->size);
          println(" ");
          toString(str,(tempCMCB->beginningAddress));
          println(str);
          toString(str,(tempCMCB->size));
          println(str);
          tempCMCB = tempCMCB->nextCMCB;
    }
}

void toString(char str[], int x){
  int i, rem, len =0,n;
  n =x;
  while(n!=0){
    len++;
    n/=10;
  }
  for(i=0; i<len; i++){
    rem = x % 10;
    x= x /10;
    str[len-(i + 1)] = rem + '0';
  }
  str[len] = '\0';

}

void insertCMCB (memoryList *list, CMCB *memBlock){
  //if nothing yet in the memoryList
  if(list->count == 0){
    list->head = memBlock;
    list->tail = memBlock;
    memBlock->nextCMCB = NULL;
    memBlock->previousCMCB = NULL;
  }
  //if the beginningAddress is greater than the head,
  //set the memBlock's next element elistual to the head, and the head's previous element elistual to the memBlock,
  //and the head elistual to the memBlock
  else if(memBlock->beginningAddress < list->head->beginningAddress){
    memBlock->nextCMCB = list->head;
    list->head->previousCMCB = memBlock;
    list->head = memBlock;
  }
  //if beginningAddress is less than the tail, insert after tail
  else if(memBlock->beginningAddress > list->tail->beginningAddress){
    list->tail->nextCMCB = memBlock;
    memBlock->previousCMCB = list->tail;
    list->tail = memBlock;
  }
  //otherwise if beginningAddress is somewhere in the middle
  else{
    CMCB *temp = list->head;
    while(temp != NULL){
      if(memBlock->beginningAddress > temp->beginningAddress){
        temp = temp->nextCMCB;
      }else{
        memBlock->previousCMCB = temp->previousCMCB;
        memBlock->previousCMCB->nextCMCB = memBlock;
        temp->previousCMCB = memBlock;
        memBlock->nextCMCB = temp;
        temp = NULL;
      }
    }
  }
  list->count++;
}
