#include <string.h>
#include "mpx_supt.h"
#include "print.h"
#include "time.h"
#include <core/io.h>

//needs fixing just a start
int gettime(){
  //testing output
char time[9]= "00:00:00";


  //hours
  outb(0x70, 0x04);
  BCDtoStr(inb(0x71), time);


  //minutes
  outb(0x70, 0x02);
   BCDtoStr(inb(0x71), &time[3]);

  //seconds
  outb(0x70, 0x00);
  BCDtoStr(inb(0x71), &time[6]);


  print("Current time: ");
  println(time);
  return 0;
}
int settime(char* time){
cli();


//hours
outb(0x70, 0x04);
outb(0x71, StrtoBCD(time));

//minutes
outb(0x70, 0x02);
outb(0x71, StrtoBCD(&time[3]));

//seconds
outb(0x70, 0x00);
outb(0x71, StrtoBCD(&time[6]));

print("Time has been set to: ");
println(time);
sti();
return 0;
}

int intToBCD(int val){
 return ((val/10)<<4 ) | (val % 10);
}

int BCDtoInt(int val){
 return ((val & 0xF0)>> 4)*10 + (val & 0x0F);
}
int BCDtoStr(int val,char* str){
  str[0] = (val & 0xF0) + '0';
  str[1] = (val & 0x0F) + '0';
  return 0;
}
int StrtoBCD(char* str){
  int bcd;
  bcd = ((str[0] -'0') << 4) + (str[1]- '0');
  return bcd;
}
