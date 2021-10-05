// PCB Header
#include <system.h>

typedef struct {
  char [100] *processName;
  unsigned char *processClass;
  int priority;
  int stateReady;
  int stateSuspended;
  unsigned char *stackTop;
  unsigned char *stackBase;
  PCB *nextPCB;
  PCB *previousPCB;
} PCB;

void fifo_enqueue (*queue q, PCB pcb); // Emily

void priority_enqueue (*queue q, PCB pcb);// Emily

PCB* AllocatePCB(); // Anthony

void FreePCB(); // Anthony

PCB* SetupPCB(); // Jarett - its kinda funky cuz of processClass, stackTop, and stackBase

void FindPCB(); // Will

void InsertPCB(); // Emily

void RemovePCB(); // Emily

void CreatePCB(); // Jarett

void DeletePCB(); //Will

void BlockPCB(); //Jarett

void UnblockPCB();// these were all really similar

void SuspendPCB();// and should be mostly right I have to study for 422 tm

void ResumePCB();//  cuz i have the quiz wednesday I  can still hop on

void SetPCBPriority();// and help but cant do to much Hopefully this is a decent start

void ShowPCB();

void ShowReady();

void ShowBlocked();

void ShowAll();
