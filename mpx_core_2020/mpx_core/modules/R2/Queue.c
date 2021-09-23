#include <string.h>
#include <system.h>
#include <core/serial.h>
#include "PCB.h"

struct queue {
    int count;
    pcb *head;
    pcb *tail;
} queue;

struct CreateQueue(queue *st) {
  
  return st;
}
