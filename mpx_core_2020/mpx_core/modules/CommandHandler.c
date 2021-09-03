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

//needs fixing just a start
gettiime(){

  //hours
  outb(0x70, 0x04);
  inb(0x71);

  //minutes
  outb(0x70, 0x02);
  inb(0x71);

  //seconds
  outb(0x70, 0x00);
  inb(0x71);

}
}
