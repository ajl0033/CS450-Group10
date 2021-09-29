// PCB Header
#include <system.h>

typedef struct {
  char [100] *processName;
  unsigned char *processClass;
  int *priority;
  int *stateReady;
  int *stateSuspended;
  unsigned char *stackTop;
  unsigned char *stackBase;
  struct node *nextPCB;
  struct node *previousPCB;
} PCB;

void AllocatePCB();

void FreePCB();

void SetupPCB();

void FindPCB();

void InsertPCB();

void RemovePCB();

PCB CreatePCB();

void DeletePCB();

void BlockPCB();

ovid UnblockPCB();

void SuspendPCB();

void ResumePCB();

void SetPCBPriority();

void ShowPCB();

void ShowReady();

void ShowBlocked();

void ShowAll();
