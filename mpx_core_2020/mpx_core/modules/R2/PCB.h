// PCB Header
#include <system.h>

typedef struct {
  char [100] *processName;
  unsigned char *processClass;
  int priority;
  int state;
  int stateSuspended;
  unsigned char *stackTop;
  unsigned char *stackBase;
  PCB *nextPCB;
  PCB *previousPCB;
} PCB;

void fifo_enqueue (queue *q, PCB *pcb); // Emily

void priority_enqueue (queue *q, PCB *pcb);// Emily

PCB* AllocatePCB(); // Anthony

void FreePCB(); // Anthony

PCB* SetupPCB(char* [100] processName, unsigned char processClass, int priority); // Jarett - its kinda funky cuz of processClass, stackTop, and stackBase

void FindPCB(char* [100] processName); // Will

void InsertPCB(); // Emily

void RemovePCB(); // Emily

void CreatePCB(char* [100] processName, unsigned char processClass, int priority); // Jarett

void DeletePCB(char* [100] processName); //Will

void BlockPCB(char* [100] processName); //Jarett

void UnblockPCB(char* [100] processName);// these were all really similar

void SuspendPCB(char* [100] processName);// and should be mostly right - I have to study for 422 tm

void ResumePCB(char* [100] processName);//  cuz i have the quiz wednesday - I  can still hop on

void SetPCBPriority(char* [100] processName, int priority);// and help but cant do to much - Hopefully this is a decent start

void ShowPCB(char* [100] processName); // Will

void ShowReady(); // Will

void ShowBlocked(); // Will

void ShowAll(); // Will
