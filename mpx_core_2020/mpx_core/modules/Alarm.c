#include <PCB.c>
#include "print.h"
#include <string.h>
#include <system.h>
#include <core/serial.h>
#include "Alarm.h"

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
  CreatePCB("alarm", 0, 2);
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
