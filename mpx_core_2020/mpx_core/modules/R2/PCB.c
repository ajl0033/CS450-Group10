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
