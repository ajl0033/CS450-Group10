// Header for Command Handler

#include <system.h>

int comhand();

/*
  Prints the current version of the MPX and the completion date
*/
void version();

/*
  Provides usage instructions for each command
*/
void help();

/*
  Exits the command handler loop
  Execution will return to kmain() and the system will halt
*/
int shutdown();
