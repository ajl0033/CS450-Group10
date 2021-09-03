#include <system.h>

int gettime();
/*
  Allows the user to set the time
*/int settime(char* time);

/*
  Converts an integer to Binary Coded Decimal
*/
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
