#ifndef _BCDCONVERSION_H
#define _BCDCONVERSION_H



int intToBCD(int val);
/*
  Converts Binary Coded Decimal to an integer
*/
int BCDtoInt(int val);

/*
  Converts Binary Coded Decimal to a string
*/
int BCDtoStr(int val,char* str);

int StrtoBCD(char* str);

#endif
