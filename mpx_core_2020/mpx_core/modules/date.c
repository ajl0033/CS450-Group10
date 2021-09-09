#include <string.h>
#include "mpx_supt.h"
#include "print.h"
#include "date.h"
#include <core/io.h>
#include "bcdConversion.h"

/*
day of week - 0x06
day of month - 07
month - 08
year- 09

0402/2002/01
dayOfMonth&Month/year/dayOfWeek
*/

int getdate(){
char date[12] = "0000/0000/00";


//dayOfMonth
outb(0x70, 0x07);
 BCDtoStr(inb(0x71), &date[0]);

//Month
outb(0x70, 0x08);
BCDtoStr(inb(0x71), &date[2]);

//century
outb(0x70, 0x32);
BCDtoStr(inb(0x71), &date[5]);

//year
outb(0x70, 0x09);
BCDtoStr(inb(0x71), &date[7]);

//dayofweek
outb(0x70, 0x06);
BCDtoStr(inb(0x71), &date[10]);

print("\n\nCurrent Date formatted dayOfMonth&Month/year/dayOfWeek is: ");
println(date);
return 0;

}



 int setdate(){
   char cmdBuffer[100];
   int bufferSize;
   memset(cmdBuffer, '\0', 100);
   bufferSize = 99;
   print("\nEnter a date in the form dayOfMonth&Month/year/dayOfWeek\n");
   print("For day of week: Sunday = 01 -- Saturday = 07\n");
   print("Example date could be \"0402/1999/02\" - or February 4th / 1999 / Monday \n");
  sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  char date[12];

    int count = 0;
    while(count < 12) {
    date[count] = cmdBuffer[count];
    count++;
  }
//0402/2002/01
//0123/5678/10,11
//need to add more error checking
if(checkDate(date)){
  return 1;
}else{
  cli();

//dayOfMonth
outb(0x70, 0x07);
outb(0x71, StrtoBCD(&date[0]));

//month
outb(0x70, 0x08);
outb(0x71, StrtoBCD(&date[2]));

//century
outb(0x70, 0x32);
outb(0x71, StrtoBCD(&date[5]));

//year
outb(0x70, 0x09);
outb(0x71, StrtoBCD(&date[7]));

//dayofweek
outb(0x70, 0x06);
outb(0x71, StrtoBCD(&date[10]));

print("\nDate has been set in the form dayOfMonth&Month/year/dayOfWeek to: ");
println(date);
sti();
return 0;

}
}

int checkDate(char* date){
  if(
     date[4] != '/' || date[9] != '/'
 || date[0] > '3'   || date[0] < '0'
 || date[1] < '0'   || date[1] > '9'
 || date[2] > '1'
 || date[10] != '0' || date[11] > '7'
)  {

  print("\nincorrect time input1");
return 1;
}
else{
  return 0;
}
}
