#include <PCB.c>
#include "print.h"
#include <string.h>
#include <system.h>
#include <core/serial.h>

void createAlarmProcess() // Create Process
{
  CreatePCB("alarm", 0, 1);
}

void addAlarm(char* message, int time) // Command
{
  PCB* alarm = FindPCB("alarm");
  alarm->time = time;
  alarm->message = message;
}
// if (gettime() == alarm->time)
// {
//   println(alarm->message)
//   sys_req(IDLE);
//   alarmList[alarm] = null; // delete individual alarm
// }

// else if (cmdBuffer[0] == 'a' && cmdBuffer[1] == 'l' && cmdBuffer[2] == 'a' && cmdBuffer[3] == 'r' && cmdBuffer[4] == 'm') {
// int i;
// int check = 1;
// for (i=4; i<100; i++)
// {
//   if (cmdBuffer[i] != ' ')
//   {
//     print("\033[31m");
//     println("\n\n**Invalid Command**\n");
//     print("\033[37m");
//     check = 0;
//     break;
//   }
// }
//   if (check == 1)
//   {
//     println("");
//     println("\nEnter a name for the alarm...\n");
//     memset(cmdBuffer, '\0', 100);
//     sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
//     println("");
//     char name[100];
//     memset(name, '\0', 100);
//     int k;
//     for (k = 0; k < 100; k++) {
//       name[k] = cmdBuffer[k];
//     }
//     println("");
//      println("");
//     println("\nEnter the time for the alarm...\n");
//      memset(cmdBuffer, '\0', 100);
//     sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
//      println("");
//      addAlarm(name, cmdBuffer);
//    }
//  }
