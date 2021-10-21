#include <PCB.c>
#include "print.h"
#include <string.h>
#include <system.h>
#include <core/serial.h>

struct Node {
  int time;
  char message [50];
  struct Node* next;
  struct Node* previous;
} timesList;

struct timesList* head = NULL;
head = (struct timesList*)malloc(sizeof(struct timesList));

void createAlarmProcess() // Create Process
{
  CreatePCB("alarm", 0, 1);
}

void addAlarm(char* message, int alarmTime) // Command for terminal
{
  PCB* alarm = FindPCB("alarm");
  timesList* node = head;
  while (node != NULL)
  {
    node = node->next;
  }
  timesList* newNode = node->next
  newNode->time = alarmTime;
  strcpy(newNode->message, message);
}

// **** Starter code to examine if alarm is triggered or should stay IDLE ********
// **** Don't know if this needs to be in this file or the PCB.c file...
// timesList* node = head;
// while (node != NULL)
// {
// if (gettime() == node->time || gettime() > node->time)
// {
//   println(node->message)
//   sys_req(IDLE); ?
//   if (node == head)
//   {
//     head == NULL;
//   }
//   else
//   {
//   node->previous->next = node->next; // delete individual alarm
//   free(node);
// }
// }
// node = node->next;
// }


// ****** Code for commhand, can be directly pased as an else if. User types "alarm" in the terminal ********
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
