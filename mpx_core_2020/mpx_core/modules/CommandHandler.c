// Command Handler Implementation
#include <system.h>
#include <core/serial.h>
#include "mpx_supt.h"
#include "CommandHandler.h"
#include "print.h"
#include <string.h>
#include "date.h"
#include "time.h"
#include "PCB.h"
#include "Alarm.h"

// UNCOMMENT LINES - 334, 353, 372, 407-444, 446

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
  println("           \\/               \\_/    Version R3/4  ");
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
  else if (cmdBuffer[0] == 's' && cmdBuffer[1] == 'u' && cmdBuffer[2] == 's' && cmdBuffer[3] == 'p' && cmdBuffer[4] == 'e' && cmdBuffer[5] == 'n' && cmdBuffer[6] == 'd') {
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
        println("\nEnter the Process Name...\n");
        memset(cmdBuffer, '\0', 100);
        sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
        println("");
        SuspendPCB(cmdBuffer);
      }
  }
  else if (cmdBuffer[0] == 'r' && cmdBuffer[1] == 'e' && cmdBuffer[2] == 's' && cmdBuffer[3] == 'u' && cmdBuffer[4] == 'm' && cmdBuffer[5] == 'e') {
    int i;
    int check = 1;
    for (i=6; i<100; i++)
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
        println("\nEnter the Process Name...\n");
        memset(cmdBuffer, '\0', 100);
        sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
        println("");
        ResumePCB(cmdBuffer);
      }
  }
  else if (cmdBuffer[0] == 's' && cmdBuffer[1] == 'e' && cmdBuffer[2] == 't' && cmdBuffer[3] == 'p' && cmdBuffer[4] == 'r' && cmdBuffer[5] == 'i' && cmdBuffer[6] == 'o' && cmdBuffer[7] == 'r' && cmdBuffer[8] == 'i' && cmdBuffer[9] == 't' && cmdBuffer[10] == 'y') {
    int i;
    int check = 1;
    for (i=11; i<100; i++)
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
        println("\nEnter the Process Name...\n");
        memset(cmdBuffer, '\0', 100);
        sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
        println("");
        char process[100];
        memset(process, '\0', 100);
        int k;
        for (k = 0; k < 100; k++) {
          process[k] = cmdBuffer[k];
        }
        println("");
        println("\nEnter the Process Priority...\n");
        memset(cmdBuffer, '\0', 100);
        sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
        println("");
        int priority = 99;
        int check = 1;
        while (check == 1) {
          check = 0;
          if (cmdBuffer[0] == '1') { priority = 1;}
          else if (cmdBuffer[0] == '1') { priority = 1;}
          else if (cmdBuffer[0] == '2') { priority = 2;}
          else if (cmdBuffer[0] == '3') { priority = 3;}
          else if (cmdBuffer[0] == '4') { priority = 4;}
          else if (cmdBuffer[0] == '5') { priority = 5;}
          else if (cmdBuffer[0] == '6') { priority = 6;}
          else if (cmdBuffer[0] == '7') { priority = 7;}
          else if (cmdBuffer[0] == '8') { priority = 8;}
          else if (cmdBuffer[0] == '9') { priority = 9;}
          else {print("Invalid Priority.  Must be from 1 to 9.");check = 1;}
        }
        SetPCBPriority(process, priority);
      }
  }
  else if (cmdBuffer[0] == 's' && cmdBuffer[1] == 'h' && cmdBuffer[2] == 'o' && cmdBuffer[3] == 'w' && cmdBuffer[4] == 'p' && cmdBuffer[5] == 'c' && cmdBuffer[6] == 'b') {
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
        println("\nEnter the Process Name...\n");
        memset(cmdBuffer, '\0', 100);
        sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
        println("");
        ShowPCB(cmdBuffer);
      }
  }
  else if (cmdBuffer[0] == 's' && cmdBuffer[1] == 'h' && cmdBuffer[2] == 'o' && cmdBuffer[3] == 'w' && cmdBuffer[4] == 'a' && cmdBuffer[5] == 'l' && cmdBuffer[6] == 'l') {
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
        ShowAll();
      }
  }
  else if (cmdBuffer[0] == 's' && cmdBuffer[1] == 'h' && cmdBuffer[2] == 'o' && cmdBuffer[3] == 'w' && cmdBuffer[4] == 'r' && cmdBuffer[5] == 'e' && cmdBuffer[6] == 'a' && cmdBuffer[7] == 'd' && cmdBuffer[8] == 'y') {
    int i;
    int check = 1;
    for (i=9; i<100; i++)
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
        ShowReady();
      }
  }
  else if (cmdBuffer[0] == 's' && cmdBuffer[1] == 'h' && cmdBuffer[2] == 'o' && cmdBuffer[3] == 'w' && cmdBuffer[4] == 'b' && cmdBuffer[5] == 'l' && cmdBuffer[6] == 'o' && cmdBuffer[7] == 'c' && cmdBuffer[8] == 'k' && cmdBuffer[9] == 'e' && cmdBuffer[10] == 'd') {
    int i;
    int check = 1;
    for (i=11; i<100; i++)
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

      ShowBlocked();
      }
  }
  //////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////
  /////             TEMP COMMANDS                                    ///////////////
  //////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////
  // else if (cmdBuffer[0] == 'c' && cmdBuffer[1] == 'r' && cmdBuffer[2] == 'e' && cmdBuffer[3] == 'a' && cmdBuffer[4] == 't' && cmdBuffer[5] == 'e' && cmdBuffer[6] == 'p' && cmdBuffer[7] == 'c' && cmdBuffer[8] == 'b') {
  //   int i;
  //   int check = 1;
  //   for (i=9; i<100; i++)
  //   {
  //     if (cmdBuffer[i] != ' ')
  //     {
  //       print("\033[31m");
  //       println("\n\n**Invalid Command**\n");
  //       print("\033[37m");
  //       check = 0;
  //       break;
  //     }
  //   }
  //     if (check == 1)
  //     {
  //       println("");
  //       println("\nEnter the Process Name...\n");
  //       memset(cmdBuffer, '\0', 100);
  //       sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  //       println("");
  //       char process[100];
  //       memset(process, '\0', 100);
  //       int k;
  //       for (k = 0; k < 100; k++) {
  //         process[k] = cmdBuffer[k];
  //       }
  //       println("");
  //        println("");
  //       println("\nEnter the Process Class: (0 for \"system process\" or 1 for \"application\")\n");
  //        memset(cmdBuffer, '\0', 100);
  //       sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  //        println("");
  //        int check1 = 1;
  //        int class = 99;
  //        while (check1 == 1) {
  //          check1 = 0;
  //          if (cmdBuffer[0] == '0') {
  //              class = 0;
  //          } else if (cmdBuffer[0] == '1') {
  //            class = 1;
  //          } else {
  //            check1 = 1;
  //         }
  //        }
  //        println("\nEnter the Process Priority...\n");
  //        memset(cmdBuffer, '\0', 100);
  //        sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  //        println("");
  //        int priority = 99;
  //        int check = 1;
  //        while (check == 1) {
  //          check = 0;
  //          if (cmdBuffer[0] == '1') { priority = 1;}
  //          else if (cmdBuffer[0] == '0') { priority = 0;}
  //          else if (cmdBuffer[0] == '1') { priority = 1;}
  //          else if (cmdBuffer[0] == '2') { priority = 2;}
  //          else if (cmdBuffer[0] == '3') { priority = 3;}
  //          else if (cmdBuffer[0] == '4') { priority = 4;}
  //          else if (cmdBuffer[0] == '5') { priority = 5;}
  //          else if (cmdBuffer[0] == '6') { priority = 6;}
  //          else if (cmdBuffer[0] == '7') { priority = 7;}
  //          else if (cmdBuffer[0] == '8') { priority = 8;}
  //          else if (cmdBuffer[0] == '9') { priority = 9;}
  //          else {print("Invalid Priority.  Must be from 1 to 9.");check = 1;}
  //        }
  //
  //       CreatePCB(process, class, priority);
  //     }
  // }
  else if (cmdBuffer[0] == 'd' && cmdBuffer[1] == 'e' && cmdBuffer[2] == 'l' && cmdBuffer[3] == 'e' && cmdBuffer[4] == 't' && cmdBuffer[5] == 'e' && cmdBuffer[6] == 'p' && cmdBuffer[7] == 'c' && cmdBuffer[8] == 'b') {
    int i;
    int check = 1;
    for (i=9; i<100; i++)
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
        println("\nEnter the Process Name...\n");
        memset(cmdBuffer, '\0', 100);
        sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
        println("");
        DeletePCB(cmdBuffer);
      }
  }
  // else if (cmdBuffer[0] == 'b' && cmdBuffer[1] == 'l' && cmdBuffer[2] == 'o' && cmdBuffer[3] == 'c' && cmdBuffer[4] == 'k' && cmdBuffer[5] == 'p' && cmdBuffer[6] == 'c' && cmdBuffer[7] == 'b') {
  //   int i;
  //   int check = 1;
  //   for (i=8; i<100; i++)
  //   {
  //     if (cmdBuffer[i] != ' ')
  //     {
  //       print("\033[31m");
  //       println("\n\n**Invalid Command**\n");
  //       print("\033[37m");
  //       check = 0;
  //       break;
  //     }
  //   }
  //     if (check == 1)
  //     {
  //       println("");
  //       println("\nEnter the Process Name...\n");
  //       memset(cmdBuffer, '\0', 100);
  //       sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  //       println("");
  //       BlockPCB(cmdBuffer);
  //     }
  // }
  // else if (cmdBuffer[0] == 'u' && cmdBuffer[1] == 'n' && cmdBuffer[2] == 'b' && cmdBuffer[3] == 'l' && cmdBuffer[4] == 'o' && cmdBuffer[5] == 'c' && cmdBuffer[6] == 'k' && cmdBuffer[7] == 'p' && cmdBuffer[8] == 'c' && cmdBuffer[9] == 'b') {
  //   int i;
  //   int check = 1;
  //   for (i=10; i<100; i++)
  //   {
  //     if (cmdBuffer[i] != ' ')
  //     {
  //       print("\033[31m");
  //       println("\n\n**Invalid Command**\n");
  //       print("\033[37m");
  //       check = 0;
  //       break;
  //     }
  //   }
  //     if (check == 1)
  //     {
  //       println("");
  //       println("\nEnter the Process Name...\n");
  //       memset(cmdBuffer, '\0', 100);
  //       sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  //       println("");
  //       UnblockPCB(cmdBuffer);
  //     }
  // }
  else if (cmdBuffer[0] == 'y' && cmdBuffer[1] == 'i' && cmdBuffer[2] == 'e' && cmdBuffer[3] == 'l' && cmdBuffer[4] == 'd') {
    int i;
    int check = 1;
    for (i=5; i<100; i++)
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
      yield();
      print("\n\n");
    }
  }
  else if (cmdBuffer[0] == 'a' && cmdBuffer[1] == 'l' && cmdBuffer[2] == 'a' && cmdBuffer[3] == 'r' && cmdBuffer[4] == 'm') {
  int i;
  int check = 1;
  for (i=5; i<100; i++)
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
      println("\nEnter a message for the alarm...\n");
      memset(cmdBuffer, '\0', 100);
      sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
      println("");
      char message[100];
      memset(message, '\0', 100);
      int k;
      for (k = 0; k < 100; k++) {
        message[k] = cmdBuffer[k];
      }
      println("");
       println("");
      println("\nEnter the time for the alarm in the form: 'HH:MM:SS'...\n");
       memset(cmdBuffer, '\0', 100);
      sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
       println("");
       char time[6];
       memset(time, '\0', 100);
       int k2;
       for (k2 = 0; k2 < 6; k2++) {
         time[k2] = cmdBuffer[k2];
       }
       addAlarm(message, time);
     }
   }
   else if (cmdBuffer[0] == 'l' && cmdBuffer[1] == 'o' && cmdBuffer[2] == 'a' && cmdBuffer[3] == 'd' && cmdBuffer[4] == 'r' && cmdBuffer[5] == '3') {
     int i;
     int check = 1;
     for (i=6; i<100; i++)
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
        loadr3(1);
     }
   }
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
  else {
    print("\033[31m");
    println("\n\n**Invalid Command**\n");
    print("\033[37m");
  }
  sys_req(IDLE, DEFAULT_DEVICE, NULL, NULL);
  }
  return 0;
}


void version() {
  println("");
  println("");
  println("------------------------------");
  println("Current Version: R3/4 - 10/21/2021");
  println("------------------------------\n");
}

void help() {
  println("");
  println("");
  println("-------------------------------------------------------------------------");
  println("version:     Prints the current version of MPX and the completion date");
  println("getdate:     Retrieves the current date");
  println("setdate:     Sets the current date (MM/DD/YYYY)");
  println("gettime:     Retrieves the current time of day");
  println("settime:     Sets the current time of day (HH:MM:SS)");
  println("shutdown:    Exits command handler loop, bringing the system to a halt");
  println("suspend:     Places a PCB in the suspeneded state and reinserts it into\n             the apropriate queue");
  println("resume:      Places a PCB in the suspeneded state and reinserts it into\n             the apropriate queue");
  println("setpriority: Sets the priority of a given PCB,and reinserts it into the\n             apropriate queue");
  println("showpcb:     Displays the process name, class, state, suspended status,\n             and priority of a given PCB");
  println("showall:     Displays the process name, class, state, suspended status,\n             and priority of all PCBs");
  println("showready:   Displays the process name, class, state, suspended status,\n             and priority of all PCBs in the ready queue");
  println("showblocked: Displays the process name, class, state, suspended status,\n             and priority of all PCBs in the blocked queue");
  println("deletepcb:   Removes a given PCB and frees the accociated memory");
  println("alarm:       Sets a new alarm with a message at a given time");
  println("yield:       Causes commhand to yield to other processes\n");
  println("loadr3:       Load processes for R3 testing purposes\n");
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
      removedReadyHead();
      sys_req(EXIT, DEFAULT_DEVICE, NULL, NULL);
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
