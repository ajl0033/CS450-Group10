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
  println("           \\/               \\_/    Version R2  ");
  println("                                  ____________");
  println("");
  print("\033[34m"); // BLUE
  println("================================================");
  println("");
  print("\033[33m"); // YELLOW
  println("Welcome to the MPX! Type 'help' for a list of commands...\n");
  print("\033[37m");
  while(!quit) {

  // get a command
  memset(cmdBuffer, '\0', 100);
  bufferSize = 99;

  // reset size before each call to read
  sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  int i;
  for (i = 0; i<100; i++)
  {
    if ((cmdBuffer[i] >= 97 && cmdBuffer[i] <= 122) || (cmdBuffer[i] >= 48 && cmdBuffer[i] <= 57) || (cmdBuffer[i] >= 65 && cmdBuffer[i] <= 90) || (cmdBuffer[i] == 47) || (cmdBuffer[i] == 92))
    {

    } else
    {
      cmdBuffer[i] = ' ';
    }
  }
  if (cmdBuffer[0] == 'h' && cmdBuffer[1] == 'e' && cmdBuffer[2] == 'l' && cmdBuffer[3] == 'p') {
    int i;
    int check = 1;
    for (i=4; i<100; i++)
    {
      if (cmdBuffer[i] != ' ')
      {
        print("\033[31m");
        println("\n\n**Invalid Command**\n");
        print("\033[37m");
        check = 0;
        break;
      }
    }
    if (check == 1)
    {
      help();
    }
  }
  else if (cmdBuffer[0] == 'v' && cmdBuffer[1] == 'e' && cmdBuffer[2] == 'r' && cmdBuffer[3] == 's' && cmdBuffer[4] == 'i' && cmdBuffer[5] == 'o' && cmdBuffer[6] == 'n') {
    int i;
    int check = 1;
    for (i=7; i<100; i++)
    {
      if (cmdBuffer[i] != ' ')
      {
        print("\033[31m");
        println("\n\n**Invalid Command**\n");
        print("\033[37m");
        check = 0;
        break;
      }
    }
    if (check == 1)
    {
      version();
    }
  }
  else if ((cmdBuffer[0] == 'g' && cmdBuffer[1] == 'e' && cmdBuffer[2] == 't' && cmdBuffer[3] == 'd' && cmdBuffer[4] == 'a' && cmdBuffer[5] == 't' && cmdBuffer[6] == 'e')) {
    int i;
    int check = 1;
    for (i=7; i<100; i++)
    {
      if (cmdBuffer[i] != ' ')
      {
        print("\033[31m");
        println("\n\n**Invalid Command**\n");
        print("\033[37m");
        check = 0;
        break;
      }
    }
    if (check == 1)
    {
      getdate();
    }
  }
  else if (cmdBuffer[0] == 's' && cmdBuffer[1] == 'e' && cmdBuffer[2] == 't' && cmdBuffer[3] == 'd' && cmdBuffer[4] == 'a' && cmdBuffer[5] == 't' && cmdBuffer[6] == 'e') {
    int i;
    int check = 1;
    for (i=7; i<100; i++)
    {
      if (cmdBuffer[i] != ' ')
      {
        print("\033[31m");
        println("\n\n**Invalid Command**\n");
        print("\033[37m");
        check = 0;
        break;
      }
    }
    if (check == 1)
    {
      setdate();
    }
  }
  else if (cmdBuffer[0] == 'g' && cmdBuffer[1] == 'e' && cmdBuffer[2] == 't' && cmdBuffer[3] == 't' && cmdBuffer[4] == 'i' && cmdBuffer[5] == 'm' && cmdBuffer[6] == 'e') {
    int i;
    int check = 1;
    for (i=7; i<100; i++)
    {
      if (cmdBuffer[i] != ' ')
      {
        print("\033[31m");
        println("\n\n**Invalid Command**\n");
        print("\033[37m");
        check = 0;
        break;
      }
    }
    if (check == 1)
    {
      gettime();
    }
  }
  else if (cmdBuffer[0] == 's' && cmdBuffer[1] == 'e' && cmdBuffer[2] == 't' && cmdBuffer[3] == 't' && cmdBuffer[4] == 'i' && cmdBuffer[5] == 'm' && cmdBuffer[6] == 'e') {
    int i;
    int check = 1;
    for (i=7; i<100; i++)
    {
      if (cmdBuffer[i] != ' ')
      {
        print("\033[31m");
        println("\n\n**Invalid Command**\n");
        print("\033[37m");
        check = 0;
        break;
      }
    }
    if (check == 1)
    {
      println("");
      println("\nEnter the time in the form: 'HH:MM:SS' \n");
      memset(cmdBuffer, '\0', 100);
      sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
      println("");
      settime(cmdBuffer);
    }
  }
  else if (cmdBuffer[0] == 's' && cmdBuffer[1] == 'h' && cmdBuffer[2] == 'u' && cmdBuffer[3] == 't' && cmdBuffer[4] == 'd' && cmdBuffer[5] == 'o' && cmdBuffer[6] == 'w' && cmdBuffer[7] == 'n') {
    int i;
    int check = 1;
    for (i=8; i<100; i++)
    {
      if (cmdBuffer[i] != ' ')
      {
        print("\033[31m");
        println("\n\n**Invalid Command**\n");
        print("\033[37m");
        check = 0;
        break;
      }
    }
    if (check == 1)
    {
      quit = shutdown();
    }
  }
  else {
    print("\033[31m");
    println("\n\n**Invalid Command**\n");
    print("\033[37m");
  }
  }
  return 0;
}


void version() {
  println("");
  println("");
  println("------------------------------");
  println("Current Version: R2 - 10/01/2021");
  println("------------------------------\n");
}

void help() {
  println("");
  println("");
  println("-------------------------------------------------------------------------");
  println("version:  Prints the current version of MPX and the completion date");
  println("getdate:  Retrieves the current date");
  println("setdate:  Sets the current date (MM/DD/YYYY)");
  println("gettime:  Retrieves the current time of day");
  println("settime:  Sets the current time of day (HH:MM:SS)");
  println("shutdown: Exits command handler loop, bringing the system to a halt");
  println("-------------------------------------------------------------------------\n");
}

int shutdown() {
  char cmdBuffer[100];
  int bufferSize;
  print("\033[31m");
  println("\n\nAre you sure you want to quit and shutdown? y/n\n");
  print("\033[37m");
  while(1)
  {
    memset(cmdBuffer, '\0', 100);
    bufferSize = 99;
    sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);

    if ((cmdBuffer[1] >= 97 && cmdBuffer[1] <= 122) || (cmdBuffer[1] >= 48 && cmdBuffer[1] <= 57) || (cmdBuffer[1] >= 65 && cmdBuffer[1] <= 90) || (cmdBuffer[1] == 47) || (cmdBuffer[1] == 92))
    {
      print("\033[31m");
      println("\n\nAre you sure you want to quit and shutdown? y/n\n");
      print("\033[37m");
    }
    else if (cmdBuffer[0] == 'y' || cmdBuffer[0] == 'Y') {
      println("");
      return 1;
    }
    else if (cmdBuffer[0] == 'n' || cmdBuffer[0] == 'N') {
      println("");
      return 0;
    }
    else {
      print("\033[31m");
      println("\n\nAre you sure you want to quit and shutdown? y/n\n");
      print("\033[37m");
    }
  }
}
