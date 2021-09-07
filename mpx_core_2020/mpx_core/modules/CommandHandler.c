// Command Handler Implementation
#include <system.h>
#include <core/serial.h>
#include "mpx_supt.h"
#include "CommandHandler.h"
#include "print.h"
#include <string.h>

int comhand(){
  char cmdBuffer[100];
  int bufferSize;
  int quit=0;

  while(!quit) {
    println("Welcome to the MPX! What would you like to do?\n1: Help\n2: Version\n3: Get Date\n4: Set Date\n5: Get Time\n6: Set Time\n7: Shutdown");
  // get a command
  memset(cmdBuffer, '\0', 100);
  bufferSize = 99;
  // reset size before each call to read
  sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 1) {
    help();
  }
  else if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 2) {
    version();
  }
  else if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 3) {
    //getdate();
  }
  else if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 4) {
    //setdate();
  }
  else if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 5) {
    //gettime();
  }
  else if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 6) {
    //settime();
  }
  else if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 7) {
    //shutdown();
  }
  // process the command
  // see if quit was entered
  }
  return 1;
}


void version() {
  println("R1, 9/6/2021");
}

void help() {
  println("Version: Prints the current version of MPX and the completion date");
  println("Get Date: Retrieves the current date");
  println("Set Date: Sets the current date (Hours, minutes, seconds)");
  println("Get Time: Retrieves the current time of day");
  println("Set Time: Sets the current time of day (Hours, minutes, seconds)");
  println("Shutdown: Exits command handler loop, bringing the system to a halt");
}

//int shutdown() {
  // println("Are you sure you want to quit and shutdown? Y: 1, N: 2");
  // int quit;
  // scanf("%d", &quit);
  // if (quit == 1) {
  //   return quit;
  // }
  // else if (quit == 2) {
  //   return quit;
  // }
//}
