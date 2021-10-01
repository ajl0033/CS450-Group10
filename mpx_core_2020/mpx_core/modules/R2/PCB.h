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

PCB* AllocatePCB(); // Anthony

void FreePCB(); // Anthony

void SetupPCB(); // Jarett

void FindPCB(); // Will

void InsertPCB(); // Emily

void RemovePCB(); // Emily

PCB CreatePCB(); // Jarett

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
