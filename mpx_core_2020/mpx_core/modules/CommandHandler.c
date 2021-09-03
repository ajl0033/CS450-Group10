// Command Handler Implementation

#include <system.h>
#include <core/serial.h>
#include "CommandHandler.h"
#include <string.h>
#include "mpx_supt.h"
#include "print.h"
#include <core/io.h>
#include "time.h"

int comhand(){
  char cmdBuffer[100];
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
