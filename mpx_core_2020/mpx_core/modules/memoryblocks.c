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

u32int initialize_heap(u32int size){
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

void allocate_memory(u32int bytes)
{
  // if nothing in allocated list:
  // need to declare a cmcb and put it in allocated_list
  // top(free_list.head?)->beginningAddress? += intbytes + sizeof(cmcb)
  //  else
  //  move top->beginninng adress the same way after placing it at the end of allocated_list

  //there is 0 error checking here, if there isnt size it'll break
  // but it should work if there is room within free, error checking is for when it works
  CMCB* temp = (CMCB*)start_of_memory;
  temp->size = bytes;
  temp->type = 1;

  //could hard code it in each timemp; but lets see if this works
  CMCB* top = free_list.head;

  if(allocated_list.count == 0){
  allocated_list.head = temp;
  allocated_list.tail = temp;
  temp->beginningAddress = start_of_memory;//top->beginningAddress; could be either - one right one wrong
  top->beginningAddress +=  (bytes + sizeof(CMCB));

    }else if(allocated_list.count == 1){
      allocated_list.tail = temp;
      //i am confused between the usage of . and -> -- anthony please clear that up
      allocated_list.head->previousCMCB = temp;
      temp->nextCMCB = allocated_list.head;
      temp->beginningAddress = top->beginningAddress;
      //previous line should be correct b/c allocated_list already starts at the start_of_memory
      top->beginningAddress +=  (bytes + sizeof(CMCB));

  }     else{
          allocated_list.tail->previousCMCB = temp;
          temp->nextCMCB = allocated_list.tail;
          allocated_list.tail = temp;
          temp->beginningAddress = top->beginningAddress;
          top->beginningAddress += (bytes + sizeof(CMCB));
          }
}

void free_memory(int address) // Will
{
  CMCB* tempAllocated = allocated_list.head;
  while (tempAllocated != NULL)
  {
    if (tempAllocated->beginningAddress == (u32int)address)
    {
      // Allocate to free list
      allocate_memory(tempAllocated->size);
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
    if ((tempFree->size + sizeof(LMCB) + 1) == (tempFreeNext->beginningAddress)) // Check if adjacent blocks are both free
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
      tempFree = tempFree->nextCMCB;
  }
}

//0 = false ----- 1 = true
int IsEmpty(){
  return allocated_list.count == 0;
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
          toString(str,(tempCMCB->beginningAddress));
           println(str);
           toString(str,(tempCMCB->size));
           println(str);
          //could be changed in both depending on how we define the list
          tempCMCB = tempCMCB->previousCMCB;
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
          toString(str,(tempCMCB->beginningAddress));
         println(str);
         toString(str,(tempCMCB->size));
         println(str);
          tempCMCB = tempCMCB->previousCMCB;
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
