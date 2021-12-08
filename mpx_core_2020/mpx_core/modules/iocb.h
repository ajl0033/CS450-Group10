#ifndef _IOCB_H
#define _IOCB_H

#include <system.h>
#include "PCB.h"
#include "dcb.h"
enum iocb_status {NOTHING, READING, WRITING};

typedef struct iocb{
  int count;
  PCB *pcb;
  dcb *dcb;
  int events;
  enum iocb_status status;
  struct iocb *next;
  struct iocb *previous;

} iocb;

typedef struct queue {
    int count;
    iocb *head;
    iocb *tail;
} queue;

int isEmpty(queue *q);



#endif
