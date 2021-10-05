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

PCB* SetupPCB(); // Jarett

void FindPCB(); // Will

void InsertPCB(); // Emily

void RemovePCB(); // Emily

void CreatePCB(); // Jarett

void DeletePCB(); //Will

void BlockPCB();

void UnblockPCB();

void SuspendPCB();

void ResumePCB();

void SetPCBPriority();

void ShowPCB();

void ShowReady();

void ShowBlocked();

void ShowAll();
