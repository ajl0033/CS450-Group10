// Command Handler Implementation
#include <system.h>
#include <kernel/core/serial.h>
#include <kernel/core/serial.c>
#include <mpx_supt.c>
#include "CommandHandler.h"
#include <string.h>

intcomhand(){
  charcmdBuffer[100];
  int bufferSize;
  int quit=0;
  char welcome[] = "Welcome to the MPX! What would you like to do?\n1: Help\n2: Version\n3: Get Date\n4: Set Date\n5: Get Time\n6: Set Time\n7: Shutdown";

  while(!quit) {
    char * strcpy(char* charcmdBuffer, const char* welcome, size_t welcome);
    sys_req(WRITE, DEFAULT_DEVICE, charcmdBuffer, &bufferSize);
  // get a command
  memset(buffer,‘\0’,   100);
  bufferSize = 99;
  // reset size before each call to read
  sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 1) {
    help();
  }
  else if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 2) {
    version();
  }
  else if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 3) {
    getdate();
  }
  else if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 4) {
    setdate();
  }
  else if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 5) {
    gettime();
  }
  else if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 6) {
    settime();
  }
  else if (sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize) == 7) {
    shutdown();
  }
  // process the command
  // see if quit was entered
}
void version() {
  char version[] = "R1, 9/5/2021";
  char * strcpy(char* charcmdBuffer, const char* version, size_t version);
  sys_req(WRITE,DEFAULT_DEVICE,charcmdBuffer,&bufferSize);
}

void help() {

}

int shutdown() {
  char shutdown[] = "Are you sure you want to quit and shutdown? Y: 1, N: 2";
  char * strcpy(char* charcmdBuffer, const char* shutdown, size_t shutdown);
  sys_req(WRITE,DEFAULT_DEVICE,charcmdBuffer,&bufferSize);
  int quit;
  scanf("%d", &quit);
  if (quit == 1) {
    return quit;
  }
  else if (quit == 2) {
    return quit;
  }
}

void getdate() {

}

void setdate() {

}

void gettime() {

}

void settime() {

}
}
