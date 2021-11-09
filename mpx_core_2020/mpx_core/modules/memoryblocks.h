#ifndef _MEMORYBLOCKS_H
#define _MEMORYBLOCKS_H
#include <system.h>

typedef struct CMCB{
  int type; //free is 0 and allocated is 1
  int beginningAddress;
  int size;
  char name[20];
  struct CMCB *nextCMCB;
  struct CMCB *previousCMCB;
} CMCB;

typedef struct LMCB{
  int type; //free is 0 and allocated is 1
  int size;
} LMCB;

struct block {
  int count;
  CMCB *head;
  CMCB *tail;
  //LMCB *tail;
} memoryList;

void initialize_heap(int size);

void allocate_memory(int bytes);

void free_memory(); // Will



#endif
