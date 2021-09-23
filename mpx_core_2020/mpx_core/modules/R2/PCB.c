// PCB Implementation
#include <string.h>
#include <system.h>
#include <core/serial.h>
#include "PCB.h"

struct PCB {
  char [100] *processName;
  unsigned char *processClass;
  int *priority;
  int *stateReady;
  int *stateSuspended;
  unsigned char *stackTop;
  unsigned char *stackBase;
  struct node *nextPCB;
  struct node *previousPCB;
}
