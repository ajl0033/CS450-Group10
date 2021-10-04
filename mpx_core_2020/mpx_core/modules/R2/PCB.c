// PCB Implementation
#include <string.h>
#include <system.h>
#include <core/serial.h>
#include "PCB.h"
#include <Queue.c>

Struct ready = CreateQueue();  // Is this how you do it??? Hahaha
Struct blocked = CreateQueue();
Struct SuspendedReady = CreateQueue();
Struct SuspendedBlocked = CreatQueue();

PCB* AllocatePCB()
{
  sys_alloc_mem(PCB);
  PCB* pcb;
  return pcb;
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
  // Search each queue for process. Null if not found, else return PCB.
  // How do you access the queues, and how are the queues initialized.
  // Will will figure this out at some point! Studying right now for 450 and 320!
  for (int i = 0; i < ready->count; i++)
  {
    // If process = processName, return PCB
  }
  for (int i = 0; i < blocked->count; i++)
  {
    // If process = processName, return PCB
  }
  for (int i = 0; i < SuspendedReady->count; i++)
  {
    // If process = processName, return PCB
  }
  for (int i = 0; i < SuspendedBlocked->count; i++)
  {
    // If process = processName, return PCB
  }
  return null;
}

void DeletePCB(char* processName)
{
  PCB* pcb = FindPCB(processName);
  FreePCB(pcb);
}
