#include "mpx_supt.h"
#include "serial.h"
#include <system.h>
#include <string.h>
#include "print.h"

/*
  process attempts to write a  message to the serial device, used for R6 testing
  This should be the first test process executed when thesting R6.
*/
void COMWRITE(){
  char msg[50];
  int count = 0;

  memset(msg, '\0', sizeof(msg));
  strcpy(msg, "COMWRITE is writing a message. \n");
  count = strlen(msg);

  //write message
  sys_req(WRITE, DEFAULT_DEVICE, msg, &count);
  //exit
  sys_req(EXIT, DEFAULT_DEVICE, NULL, NULL);

}

/*
  process writes a prompt to the serial device and then reads user input which is them printed
  back to the device
*/
void COMREAD(){
  char outputMsg[50];
  int outputCount = 0;
  char inputBuffer[100];
  int inputCount = 100;

  memset(outputMsg, '\0', sizeof(outputMsg));
  memset(inputBuffer, '\0', sizeof(inputBuffer));

  strcpy(outputMsg, "COMREAD: Please input a message. \n");
  outputCount = strlen(outputMsg);

  //write prompt
  sys_req(WRITE, DEFAULT_DEVICE, outputMsg, &outputCount);
  //we should not meed to idle
  //sys_req(IDLE, DEFAULT_DEVICE, NULL, NULL);

  //read user input
  sys_req(READ, DEFAULT_DEVICE, inputBuffer, &inputCount);

  //echo user input to screen
  inputCount = strlen(inputBuffer);
    sys_req(WRITE, DEFAULT_DEVICE, inputBuffer, &inputCount);

    //exit
    sys_req(EXIT, DEFAULT_DEVICE, NULL, NULL);

}

/*
  process attempts to write a  message to the serial device 25 times then exits
*/
void IOCOM25(){
  char msg[50];
  int count = 0;
  int printCount = 0;

  memset(msg, '\0', sizeof(msg));
  strcpy(msg, "IOCOM25 Writing a message. \n");

  while(printCount < 25){
    count = strlen(msg);
    //write message
    sys_req(WRITE, DEFAULT_DEVICE, msg, &count);
    printCount++;
    sys_req(IDLE, DEFAULT_DEVICE, NULL, NULL);
  }
  //exit
    sys_req(EXIT, DEFAULT_DEVICE, NULL, NULL);

}

/*
  process attempts to write a  message to the serial device until suspeneded and terminated
*/
void IOCOM(){
  char msg[50];
  int count = 0;

  memset(msg, '\0', sizeof(msg));
  strcpy(msg, "IOCOM Writing a message. \n");
  count = strlen(msg);
  sys_req(WRITE, DEFAULT_DEVICE, msg, &count);

  memset(msg, '\0', sizeof(msg));
  strcpy(msg, "IOCOM still writing. \n");
  count = strlen(msg);

  while(1){
    //idles
    sys_req(IDLE, DEFAULT_DEVICE, NULL, NULL);
    //write a message
    sys_req(WRITE, DEFAULT_DEVICE, msg, &count);
    count = strlen(msg);
  }
  //exit
   sys_req(EXIT, DEFAULT_DEVICE, NULL, NULL);
}
