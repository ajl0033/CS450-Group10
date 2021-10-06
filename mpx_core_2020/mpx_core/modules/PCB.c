// PCB Implementation
#include <string.h>
#include <system.h>
#include "mpx_supt.h"
#include <core/serial.h>
#include "PCB.h"
#include "print.h"

/*
stateReady = 0,1 or 2 ---- 0 = ready -- 1 = running -- 2 = blocked
stateSuspended = 0,1 ---- 0 = not suspended -- 1 = suspended
^this can be changed but its how i coded it

Need to figure out what to do with processClass, stackTop, and stackBase in SetupPCB

test for will
*/


queue ready= {0,NULL,NULL};
queue blocked = {0,NULL,NULL};
queue SuspendedReady= {0,NULL,NULL};
queue SuspendedBlocked= {0,NULL,NULL};

//for blocked queue
void fifo_enqueue (queue *q, PCB *pcb){
  //if nothingg is in the queue yet, set the head and tail to the new pcb
  if(q->count == 0){

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
}void priority_enqueue (queue *q, PCB *pcb){
  //if nothing yet in the queue
  if(q->count == 0){

    q->head = pcb;
    q->tail = pcb;
  }
  //if the priority is greater than the head,
  //set the pcb's next element equal to the head, and the head's previous element equal to the pcb,
  //and the head equal to the pcb
  else if(pcb->priority > q->head->priority){
    pcb->nextPCB = q->head;
    q->head->previousPCB = pcb;
    q->head = pcb;
  }
  //if priority is less than the tail, insert after tail
  else if(pcb->priority <= q->tail->priority){
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



PCB* AllocatePCB()
{
  PCB* pcb = sys_alloc_mem(sizeof(PCB));
  pcb->stackBase = pcb->stack;
  pcb->stackTop = pcb->stackBase + 1024;
  return pcb;
}

PCB* SetupPCB(char* processName, int processClass, int priority){
  // I'm not sure what to do with process class, stackTop, and stackBase.

  PCB* pcb = AllocatePCB();
  pcb->processName = processName;

  //so I'm not really sure what processClass is, I've read the slide a few times :(



  pcb->processClass = processClass;


  pcb->priority = priority;
  // automatically put them in notsuspended and ready state?
  pcb->state = 0;
  pcb->stateSuspended = 0;

  return pcb;
}

void FreePCB(PCB* pcb)
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

  print("PROCESS NAME:     ");
  println(processName);
  PCB* tempReady = ready.head;
  PCB* tempBlocked = blocked.head;
  PCB* tempSReady = SuspendedReady.head;
  PCB* tempSBlocked = SuspendedBlocked.head;

  while (tempReady != NULL)
  {
    print("TEMP PROCESS NAME:    ");
    println(tempReady->processName);

    // If process = processName, return PCB
    if (strcmp(tempReady->processName, processName))
    {
      println("RETURN READY");
      return tempReady;
    }
    tempReady = tempReady->previousPCB;
  }
  while (tempBlocked != NULL)
  {
    // If process = processName, return PCB
    if (strcmp(tempBlocked->processName, processName))
    {
      return tempBlocked;
    }
    tempBlocked = tempBlocked->previousPCB;
  }
  while (tempSReady != NULL)
  {
    // If process = processName, return PCB
    if (strcmp(tempSReady->processName, processName))
    {
      return tempSReady;
    }
    tempSReady = tempSReady->previousPCB;
  }
  while (tempSBlocked != NULL)
  {
    // If process = processName, return PCB
    if (strcmp(tempSBlocked->processName, processName))
    {
      return tempSBlocked;
    }
    tempSBlocked = tempSBlocked->previousPCB;
  }
  return NULL;
}

void DeletePCB(char* processName)
{
  PCB* pcb = FindPCB(processName);
  RemovePCB(pcb);
  FreePCB(pcb);
}

void InsertPCB(PCB* pcb){
  // i Changed 1 to 0 for stateReady - we might need to mess with this but i dont know how
  // I dont know what to do for the running state but it exists ? - Jarett
  // Then made some changes for suspended states but im pretty sure those r right

  //if not suspended
  if(pcb->stateSuspended == 0){

    if(pcb->state == 0){
      priority_enqueue(&ready,pcb);
    }else{
      fifo_enqueue(&blocked,pcb);
    }
  }

  //else suspended
  else{
    if(pcb->state == 0){
      priority_enqueue(&SuspendedReady,pcb);
    }else{
      fifo_enqueue(&SuspendedBlocked,pcb);
    }
  }

}
void RemovePCB(PCB* pcb){
queue q= {0,NULL,NULL};
  //if not suspended
  if(pcb->stateSuspended == 0){

    if(pcb->state == 0){
      q = ready;
    }else{
      q = blocked;
    }
  }

  else{
    if(pcb->state == 0){
      q = SuspendedReady;
    }else{
      q = SuspendedBlocked;
    }
  }

  //if pcb to be removed is at the head, make the head now equal
  // the next pcb
  if(pcb == q.head){
    q.head->nextPCB = pcb->nextPCB->nextPCB;
    q.head = pcb->nextPCB;
  }
  //esle if it is at the tail,
  else if(pcb == q.tail){
    q.tail->previousPCB = pcb->previousPCB->previousPCB;
    q.tail = pcb->previousPCB;
  }
  else{
 pcb->previousPCB->nextPCB = pcb->nextPCB;
 pcb->nextPCB->previousPCB = pcb->previousPCB;
}
}

void CreatePCB(char* processName, int processClass, int priority){
  if(FindPCB(processName) != NULL){
    println("not unique process name");
  }
  else if(priority > 9 || priority < 0){
    println("not a valid priority");
  }else {
//how do you check if processname and class are valid?

  PCB* pcb = SetupPCB(processName,processClass,priority);
//always put into ready queue because you never get the chance to change it at this point
// unless thats changed in SetupPCB
  priority_enqueue(&ready,pcb);
  println(pcb->processName);
  if (pcb->processClass == 1) {
    println("Class: Application");
  } else if (pcb->processClass == 0) {
    println("Class: System Process");
  }
  if (pcb->priority == 0) {println("Priority: 0");}
  else if (pcb->priority == 1) {println("Priority: 1");}
  else if (pcb->priority == 2) {println("Priority: 2");}
  else if (pcb->priority == 3) {println("Priority: 3");}
  else if (pcb->priority == 4) {println("Priority: 4");}
  else if (pcb->priority == 5) {println("Priority: 5");}
  else if (pcb->priority == 6) {println("Priority: 6");}
  else if (pcb->priority == 7) {println("Priority: 7");}
  else if (pcb->priority == 8) {println("Priority: 8");}
  else if (pcb->priority == 9) {println("Priority: 9");}
  }
}

void BlockPCB(char* processName){
  if(FindPCB(processName) == NULL){
    println("Name must be valid");
  }else{
  //might need to be PCB* but not sure
  PCB* pcb = FindPCB(processName);
  pcb->state = 2;

  //could move removePCB to the top but i have no clue tbh
  RemovePCB(pcb);
  InsertPCB(pcb);
}
}


//same as block but changed 2 to a 0
void UnblockPCB(char* processName){
  if(FindPCB(processName) == NULL){
    println("Name must be valid");
  }else{
  //might need to be PCB* but not sure
  PCB* pcb = FindPCB(processName);
  pcb->state = 0;

  RemovePCB(pcb);
  InsertPCB(pcb);
}
}

//same as block or unblock but change stateSuspended instead
void SuspendPCB(char* processName){
  if(FindPCB(processName) == NULL){
    println("Name must be valid");
  }else{
  //might need to be PCB* but not sure
  PCB* pcb = FindPCB(processName);
  pcb->stateSuspended = 1;

  RemovePCB(pcb);
  InsertPCB(pcb);
}
}

//same as suspend but 1 to 0
void ResumePCB(char* processName){
  if(FindPCB(processName) == NULL){
    println("Name must be valid");
  }else{
  //might need to be PCB* but not sure
  PCB* pcb = FindPCB(processName);
  pcb->stateSuspended = 0;

  RemovePCB(pcb);
  InsertPCB(pcb);
}
}

//pretty similar to the rest - might need to mess with removing it from its queue
void SetPCBPriority(char* processName, int priority){
  if(FindPCB(processName) != NULL){
    println("not unique process name");
  }
  else if (priority > 9 || priority < 0){
    println("not a valid priority");
  }else{
    PCB* pcb = FindPCB(processName);
    pcb->priority = priority;

    RemovePCB(pcb);
    InsertPCB(pcb);
  }
}

void ShowPCB(char* processName){
  if(FindPCB(processName) == NULL)
  {
    println("Process does not exist!");
  }
  else
  {
    PCB* pcb = FindPCB(processName);
    println("");
    println(processName);
    if (pcb->processClass == 0) {
      println("Process Class: System Process");
    } else if (pcb->processClass == 1) {
      println("Process Class: Application");
    }
    if (pcb->state == 0)
    {
      println("Ready");
    }
    else if (pcb->state == 1)
    {
      println("Running");
    }
    else
    {
      println("Blocked");
    }
    if (pcb->stateSuspended == 0)
    {
      println("Not Suspended");
    }
    else
    {
      println("Suspended");
    }
    if (pcb->priority == 1)
    {
      println("Priority: 1");
    }
    else if (pcb->priority == 2)
    {
      println("Priority: 2");
    }
    else if (pcb->priority == 3)
    {
      println("Priority: 3");
    }
    else if (pcb->priority == 4)
    {
      println("Priority: 4");
    }
    else if (pcb->priority == 5)
    {
      println("Priority: 5");
    }
    else if (pcb->priority == 6)
    {
      println("Priority: 6");
    }
    else if (pcb->priority == 7)
    {
      println("Priority: 7");
    }
    else if (pcb->priority == 8)
    {
      println("Priority: 8");
    }
    else if (pcb->priority == 9)
    {
      println("Priority: 9");
    }
  }
}
void ShowReady()
{
  PCB* tempReady = ready.head;
  println("\nPCB's in ready queue:");
  // if (ready.head != NULL)
  // {
  //   ShowPCB(tempReady->processName);
  // }
  while (tempReady != NULL)
  {
    ShowPCB(tempReady->processName);
    tempReady = tempReady->nextPCB;
  }
}

void ShowBlocked()
{
  PCB* tempBlocked = blocked.head;
  println("\nPCB's in blocked queue:");
  // if (blocked.head != NULL)
  // {
  //   ShowPCB(tempBlocked->processName);
  // }
  while (tempBlocked != NULL)
  {
    ShowPCB(tempBlocked->processName);
    tempBlocked = tempBlocked->nextPCB;
  }
}

void ShowAll()
{
  println("");
  ShowReady();
  println("");
  ShowBlocked();
  println("");
}
