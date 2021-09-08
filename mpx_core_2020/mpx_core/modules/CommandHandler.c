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
  println("Welcome to the MPX! What would you like to do?");
  while(!quit) {
    println("\n1: Help\n2: Version\n3: Get Date\n4: Set Date\n5: Get Time\n6: Set Time\n7: Shutdown\n");
  // get a command
  memset(cmdBuffer, '\0', 100);
  bufferSize = 99;
  // reset size before each call to read
  sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  if (cmdBuffer[0] == '1') {
    help();
  }
  else if (cmdBuffer[0] == '2') {
    version();
  }
  else if (cmdBuffer[0] == '3') {
    //getdate();
  }
  else if (cmdBuffer[0] == '4') {
    //setdate();
  }
  else if (cmdBuffer[0] == '5') {
    //gettime();
  }
  else if (cmdBuffer[0] == '6') {
    //settime();
  }
  else if (cmdBuffer[0] == '7') {
    quit = shutdown();
  }
  // process the command
  // see if quit was entered
  }
  return 0;
}


void version() {
  println("");
  println("");
  println("------------------------------");
  println("Current Version: R1 - 9/8/2021");
  println("------------------------------");
  println("");
}

void help() {
  println("");
  println("");
  println("-------------------------------------------------------------------------");
  println("Version:  Prints the current version of MPX and the completion date");
  println("Get Date: Retrieves the current date");
  println("Set Date: Sets the current date (W/MM/DD/YYYY)");
  println("Get Time: Retrieves the current time of day");
  println("Set Time: Sets the current time of day (HH:MM:SS)");
  println("Shutdown: Exits command handler loop, bringing the system to a halt");
  println("-------------------------------------------------------------------------");
  println("");
}

int shutdown() {
  char cmdBuffer[100];
  int bufferSize;
  memset(cmdBuffer, '\0', 100);
  bufferSize = 99;
  println("");
  println("Are you sure you want to quit and shutdown? Y: 1, N: 2");
  sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  if (cmdBuffer[0] == '1') {
    println("");
    return 1;
  }
  else if (cmdBuffer[0] == '2') {
    println("");
    return 0;
  }
  else {
    return 0;
  }
}
