#include <string.h>
#include "mpx_supt.h"
#include "print.h"
#include <core/io.h>

/*
intToBCD:
take in a int value as an arguement
returns a BCD given the int value
*/
int intToBCD(int val){
 return ((val/10)<<4 ) | (val % 10);
}

/*
BCDtoInt:
takes in a int BCD value as an arguement
returns an int given the BCD value
*/
int BCDtoInt(int val){
 return ((val & 0xF0)>> 4)*10 + (val & 0x0F);
}

/*
BCDtoStr:
takes in a BCD and a char array pointer as an arguement
returns 0 but puts the BCD into the char array
*/
int BCDtoStr(int val,char* str){
//need to add another 2 chars somehow to get year to work otherwise everyhting works
  str[0] = (val >> 4) + '0';
  str[1] = (val & 0x0F) + '0';
  return 0;
}

/*
StrtoBCD:
takes in a char array pointer as an arguement
returns the BCD of the number that was in the char array
*/
int StrtoBCD(char* str){
  int bcd;
  bcd = ((str[0] -'0') << 4) + (str[1]- '0');
  return bcd;
}
