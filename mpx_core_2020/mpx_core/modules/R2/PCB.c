// PCB Implementation
#include <string.h>
#include <system.h>
#include <core/serial.h>
#include "PCB.h"
#include <Queue.c>

//stateReady = 0,1 or 2 ---- 0 = ready - 1 = running - 2 = blocked
//stateSuspended = 0,1 ---- 0 = not suspended - 1 = suspended
queue ready= {0,NULL,NULL};
queue blocked = {0,NULL,NULL};
queue SuspendedReady= {0,NULL,NULL};
queue SuspendedBlocked= {0,NULL,NULL};

//for blocked queue
void fifo_enqueue (queue *q, PCB *pcb){
  //if nothingg is in the queue yet, set the head and tail to the new pcb
  if(count == 0){
    nextPCB = NULL;
    previousPCB = NULL;
    q->head = pcb;
    q->tail = pcb;
  }

  else{
    //set the tail's next element equal to the pcb, and the pcb's previous element equal to the tail,
    // and  finally the tail equal to the  pcb
    q->tail->nextPCB = pcb;
    pcb->previousPCB = q->tail;
    q->tail = pcb;
  }
  q->count++;
}
int priority_enqueue (queue *q, PCB *pcb){
  //if nothing yet in the queue
  if(count == 0){
    nextPCB = NULL;
    previousPCB = NULL;
    q->head = pcb;
    q->tail = pcb;
  }
  //if the priority is greater than the head,
  //set the pcb's next element equal to the head, and the head's previous element equal to the pcb,
  //and the head equal to the pcb
  else if(pcb.priority > q->head){
    pcb->nextPCB = q->head;
    q->head->previousPCB = pcb;
    q->head = pcb;
  }
  //if priority is less than the tail, insert after tail
  else if(pcb.priority <= q->tail){
    q->tail->nextPCB = pcb;
    pcb->previousPCB = q->tail;
    q->tail = pcb;
  }
  //otherwise if priority is somewhere in the middle
  else{
    PCB *temp = q->head;
    while(temp != q->tail){
      if(pcb->priority < temp->priority){
        temp = temp->nextPCB;
      }else{
        pcb->previousPCB = temp->previousPCB;
        pcb->previousPCB->nextPCB = pcb;
        temp->previousPCB = pcb;
        pcb->nextPCB = temp;
        temp = q->tail;
      }
    }
  }
  q->count++;
}


}
PCB* AllocatePCB()
{
  sys_alloc_mem(PCB);
  PCB* pcb;
  return pcb;
}

PCB* SetupPCB(char [100] processName, unsigned char processClass, int priority){
  // I'm not sure what to do with process class, stackTop, and stackBase.

  PCB = AllocatePCB();
  int nameLen = strlen(processName);
  int classLen = strlen(processClass);
  int i = 0, j = 0;

  while (i<nameLen){
    PCB.processName[i] = processName[i];
    i++
  }
  //so I'm not really sure what processClass is, I've read the slide a few times :(
  while (j<classLen){
    PCB.processClass[j] = processClass[j];
    j++
  }

  PCB.priority = priority;
  PCB.stateReady = 0;
  PCB.stateSuspended = 0;

  return PCB;
}

void createPCB(char [100] processName, unsigned char processClass, int priority){
  if(FindPCB(processName) == NULL){
    println("not unique process name")
  }
  if(priority > 9 || priority < 1){
    println("not a valid priority")
  }
//how do you check if processname and class are valid?

  SetupPCB(processName,processClass,priority);
//always put into ready queue because you never get the chance to change it at this point
    priority_enqueue(ready*,processName);
  }

void FreePCB()
{
  int check = sys_free_mem(pcb);
  if (check == -1)
  {
    print("Error freeing memory");
    return;
  } else
  {
    return;
  }
}

PCB* FindPCB(char* processName)
{
  PCB *tempReady = ready->head;
  PCB *tempBlocked = blocked->head;
  PCB *tempSReady = SuspendedReady->head;
  PCB *tempSBlocked = SuspendedBlocked->head;
  // Search each queue for process. Null if not found, else return PCB.
  while (tempReady->nextPCB != NULL)
  {
    // If process = processName, return PCB
    if (tempReady->processName = processName)
    {
      return tempReady;
    }
    tempReady = tempReady->nextPCB;
  }
  while (tempBlocked->nextPCB != NULL)
  {
    // If process = processName, return PCB
    if (tempBlocked->processName = processName)
    {
      return tempBlocked;
    }
    tempBlocked = tempBlocked->nextPCB;
  }
  while (tempSReady->nextPCB != NULL)
  {
    // If process = processName, return PCB
    if (tempSReady->processName = processName)
    {
      return tempSReady;
    }
    tempSReady = tempSReady->nextPCB;
  }
  while (tempSBlocked->nextPCB != NULL)
  {
    // If process = processName, return PCB
    if (tempSBlocked->processName = processName)
    {
      return tempSBlocked;
    }
    tempSBlocked = tempSBlocked->nextPCB;
  }
  return null;
}

void DeletePCB(char* processName)
{
  PCB* pcb = FindPCB(processName);
  FreePCB(pcb);
}

void InsertPCB(PCB* pcb){
  if(pcb->stateReady == 1){
    priority_enqueue(&ready,pcb);
  }else{
    fifo_enqueue(&blocked,pcb);
  }

}
void RemovePCB(PCB* pcb){
  FindPCB(pcb->processName);
}

void BlockPCB(char* [100] processName){
  if(FindPCB(processName == NULL)){
    println("Name must be valid")
  }
  //might need to be PCB* but not sure
  PCB = FindPCB(processName);
  PCB.stateReady = 2;
 //Do you remove it because that would clear all memory
  InsertPCB(PCB);

}
