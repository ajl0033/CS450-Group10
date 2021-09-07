#include <string.h>
#include "mpx_supt.h"
#include "print.h"
#include "time.h"
#include <core/io.h>
/*
day of week - 0x06
day of month - 07
month - 08
year- 09

1/06/09/2021
dayofweek/month/dayOfMonth/year


the way the registers are used and that we only have one char array scares
me i dont know enough about c currently to tell if this is a problem
*/

int getdate(){
char date[12] = "0/00/00/0000"

//dayofweek
outb(0x70, 0x06);
BCDtoStr(inb(0x71), date);

//Month
outb(0x70, 0x08);
BCDtoStr(inb(0x71), &date[2]);

//dayOfMonth
outb(0x70, 0x07);
 BCDtoStr(inb(0x71), &time[5]);

//year
outb(0x70, 0x09);
BCDtoStr(inb(0x71), &time[8]);

print("Current Date formatted dayOfWeek/Month/dayOfMonth/Year is: ");
println(date);
return 0;

}


int setdate(char* date){
cli()


//dayofweek
outb(0x70, 0x06);
outb(0x71, StrtoBCD(date));

//month
outb(0x70, 0x08);
outb(0x71, StrtoBCD(&date[2]));

//dayOfMonth
outb(0x70, 0x07);
outb(0x71, StrtoBCD(&time[5]));

//year
outb(0x70, 0x09);
outb(0x71, StrtoBCD(&time[8]));

print("date has been set in the form dayOfWeek/Month/dayOfMonth/Year to: ");
println(date);
sti();


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
