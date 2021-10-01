// PCB Implementation
#include <string.h>
#include <system.h>
#include <core/serial.h>
#include "PCB.h"


PCB* AllocatePCB()
{
  sys_alloc_mem(PCB);
  PCB* PCBlock;
  return PCBlock;
}

PCB* FreePCB()
{
  int check = sys_free_mem(PCBlock);
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
  // Search each queue for process. Null if not found, else return PCB.
  // How do you access the queues, and how are the queues initialized. 
  // Will will figure this out at some point! Studying right now for 450 and 320!
  return null;
}

void DeletePCB(char* processName)
{
  PCB* pcb = FindPCB(processName);
  FreePCB(pcb);
}
