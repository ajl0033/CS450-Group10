#ifndef _MEMORYBLOCKS_H
#define _MEMORYBLOCKS_H
#include <system.h>

typedef struct CMCB{
  int type; //free is 0 and allocated is 1
  u32int beginningAddress;
  int size;
  struct CMCB *nextCMCB;
  struct CMCB *previousCMCB;
} CMCB;

typedef struct LMCB{
  int type; //free is 0 and allocated is 1
  int size;
} LMCB;

typedef struct memoryList {
  int count;
  CMCB *head;
  CMCB *tail;
  //LMCB *tail;
} memoryList;

u32int initialize_heap(u32int size);

u32int allocate_memory(u32int bytes);

void free_memory(u32int address); // Will

//0 = false ----- 1 = true
int IsEmpty();

void Show_Allocated_Memory();

void Show_Free_Memory();

void toString(char str[], int x);

void insertCMCB (memoryList *list, CMCB *memBlock);


#endif
