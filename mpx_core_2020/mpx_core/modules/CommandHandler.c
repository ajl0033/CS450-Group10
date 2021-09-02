// Command Handler Implementation

#include <system.h>
#include <kernel/core/serial.c>
#include "CommandHandler.h"
#include <string.h>

intcomhand(){
  charcmdBuffer[100];
  int bufferSize;
  int quit=0;

  while(!quit) {
  // get acommand
  memset(buffer,‘\0’,   100);
  bufferSize = 99;
  // reset size before each call to read
  sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);

  // process the command
  // see if quit was entered
}
}
