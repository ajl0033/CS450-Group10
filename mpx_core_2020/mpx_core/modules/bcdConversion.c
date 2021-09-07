#include <string.h>
#include "mpx_supt.h"
#include "print.h"
#include <core/io.h>

int intToBCD(int val){
 return ((val/10)<<4 ) | (val % 10);
}

int BCDtoInt(int val){
 return ((val & 0xF0)>> 4)*10 + (val & 0x0F);
}
int BCDtoStr(int val,char* str){

  str[0] = (val >> 4) + '0';
  str[1] = (val & 0x0F) + '0';
  return 0;
}
int StrtoBCD(char* str){
  int bcd;
  bcd = ((str[0] -'0') << 4) + (str[1]- '0');
  return bcd;
}
