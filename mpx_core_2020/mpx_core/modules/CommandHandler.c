// Command Handler Implementation
#include <system.h>
#include <core/serial.h>
#include "mpx_supt.h"
#include "CommandHandler.h"
#include "print.h"
#include <string.h>
#include "date.c"
#include "time.h"
//#include "date.h"

int comhand(){
  char cmdBuffer[100];
  int bufferSize;
  int quit=0;
  println("");









  print("\e[1;1H\e[2J");
  print("\033[34m"); // BLUE
  println("");
  println("================================================");
  print("\033[33m"); // YELLOW
  println("      _____ ______________  ___");
  println("     /     \\\\______   \\   \\/  /");
  println("    /  \\ /  \\|     ___/\\     / ");
  println("   /    Y    \\    |    /     \\    ____________");
  println("   \\____|__  /____|   /___/\\  \\");
  println("           \\/               \\_/    Version R1  ");
  println("                                  ____________");
  println("");
  print("\033[34m"); // BLUE
  println("================================================");
  println("");
  print("\033[33m"); // YELLOW
  println("Welcome to the MPX! What would you like to do?");
  print("\033[37m");
  while(!quit) {
    println("\n1: Help\n2: Version\n3: Get Date\n4: Set Date\n5: Get Time\n6: Set Time\n7: Shutdown\n");
  // get a command
  memset(cmdBuffer, '\0', 100);
  bufferSize = 99;
  // reset size before each call to read
  sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  if ((cmdBuffer[1] >= 97 && cmdBuffer[1] <= 122) || (cmdBuffer[1] >= 48 && cmdBuffer[1] <= 57) || (cmdBuffer[1] >= 65 && cmdBuffer[1] <= 90) || (cmdBuffer[1] == 47) || (cmdBuffer[1] == 92))
  {
    print("\033[31m");
    println("\n\n**Invalid Command**");
    print("\033[37m");
  }
  else if (cmdBuffer[0] == '1') {
    help();
  }
  else if (cmdBuffer[0] == '2') {
    version();
  }
  else if (cmdBuffer[0] == '3') {
    getdate();
  }
  else if (cmdBuffer[0] == '4') {
    setdate();
  }
  else if (cmdBuffer[0] == '5') {
    gettime();
  }
  else if (cmdBuffer[0] == '6') {
    println("");
    println("\nEnter the time in the form: 'HH:MM:SS' \n");
    memset(cmdBuffer, '\0', 100);
    sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
    println("");
    settime(cmdBuffer);
  }
  else if (cmdBuffer[0] == '7') {
    quit = shutdown();
  }
  else {
    print("\033[31m");
    println("\n\n**Invalid Command**");
    print("\033[37m");
  }
  }
  return 0;
}


void version() {
  println("");
  println("");
  println("------------------------------");
  println("Current Version: R1 - 9/9/2021");
  println("------------------------------");
}

void help() {
  println("");
  println("");
  println("-------------------------------------------------------------------------");
  println("Version:  Prints the current version of MPX and the completion date");
  println("Get Date: Retrieves the current date");
  println("Set Date: Sets the current date (MM/DD/YYYY)");
  println("Get Time: Retrieves the current time of day");
  println("Set Time: Sets the current time of day (HH:MM:SS)");
  println("Shutdown: Exits command handler loop, bringing the system to a halt");
  println("-------------------------------------------------------------------------");
}

int shutdown() {
  char cmdBuffer[100];
  int bufferSize;
  print("\033[31m");
  println("\n\nAre you sure you want to quit and shutdown? Y: 1, N: 2\n");
  print("\033[37m");
  while(1)
  {
    memset(cmdBuffer, '\0', 100);
    bufferSize = 99;
    sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);

    if ((cmdBuffer[1] >= 97 && cmdBuffer[1] <= 122) || (cmdBuffer[1] >= 48 && cmdBuffer[1] <= 57) || (cmdBuffer[1] >= 65 && cmdBuffer[1] <= 90) || (cmdBuffer[1] == 47) || (cmdBuffer[1] == 92))
    {
      print("\033[31m");
      println("\nInvalid Input. Do you still want to shutdown? Y: 1, N: 2");
      print("\033[37m");
    }
    else if (cmdBuffer[0] == '1') {
      println("");
      return 1;
    }
    else if (cmdBuffer[0] == '2') {
      println("");
      return 0;
    }
    else {
      print("\033[31m");
      println("\nInvalid Input. Do you still want to shutdown? Y: 1, N: 2");
      print("\033[37m");
    }
  }
}
