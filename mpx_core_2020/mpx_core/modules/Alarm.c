#include "PCB.h"
#include "print.h"
#include <string.h>
#include <system.h>
#include <core/serial.h>
#include "Alarm.h"

struct Node {
  char time [6];
  char message [50];
  struct Node* next;
  struct Node* previous;
} timesList;

struct Node* head = NULL;
struct Node* newNode = NULL;
struct Node* node = NULL;
//head = (struct timesList*)malloc(sizeof(struct timesList));

void createAlarmProcess() // Create Process
{
  CreatePCB("alarm", 0, 2);
}

void addAlarm(char* message, char* alarmTime){
  //PCB* alarm = FindPCB("alarm");
  node = head;
  while (node != NULL)
  {
    node = node->next;
  }
  newNode = node->next;
  strcpy(newNode->time, alarmTime);
  strcpy(newNode->message, message);
}

// **** Starter code to examine if alarm is triggered or should stay IDLE ********
// **** Don't know if this needs to be in this file or the PCB.c file...
// timesList* node = head;
// while (node != NULL)
// {
// if (gettime() == node->time || gettime() > node->time) CHANGE to STRCMP!
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
