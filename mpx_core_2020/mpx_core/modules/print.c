#include <string.h>
#include "print.h"
#include "mpx_supt.h"

int print(char* str){
  int length;
  length = strlen(str);
  sys_req(WRITE, DEFAULT_DEVICE, str, &length);
  return 0;
}

int println(char* str){
  print(str);
  print("\n");
  return 0;
}
