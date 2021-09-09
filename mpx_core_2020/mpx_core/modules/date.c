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

04/02/2002
01/34/6789
dayOfMonth/Month/year/dayOfWeek
*/

int getdate(){
char date[11] = "00/00/0000";


//dayOfMonth
outb(0x70, 0x07);
 BCDtoStr(inb(0x71), &date[0]);

//Month
outb(0x70, 0x08);
BCDtoStr(inb(0x71), &date[3]);

//century
outb(0x70, 0x32);
BCDtoStr(inb(0x71), &date[6]);

//year
outb(0x70, 0x09);
BCDtoStr(inb(0x71), &date[8]);

//dayofweek
// outb(0x70, 0x06);
// BCDtoStr(inb(0x71), &date[10]);

print("\n\nCurrent Date formatted dayOfMonth/Month/year is: ");
println(date);
return 0;

}



 int setdate(){
   char cmdBuffer[100];
   int bufferSize;
   memset(cmdBuffer, '\0', 100);
   bufferSize = 99;
   print("\n\nEnter a date in the form dayOfMonth/Month/year\n");
   print("Example date could be \"04/02/1999\" - or February 4th / 1999 \n\n");
  sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  char date[11];

    int count = 0;
    while(count < 10) {
    date[count] = cmdBuffer[count];
    count++;
  }
//0402/2002
//0123/5678
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
outb(0x71, StrtoBCD(&date[3]));

//century
outb(0x70, 0x32);
outb(0x71, StrtoBCD(&date[6]));

//year
outb(0x70, 0x09);
outb(0x71, StrtoBCD(&date[8]));

//dayofweek
// outb(0x70, 0x06);
// outb(0x71, StrtoBCD(&date[10]));

print("\n\nDate has been set in the form dayOfMonth/Month/year to: ");
print(date);
println("");
sti();
return 0;

}
}
// 04/02/1999
// 01/34/6789
//dayOfMonth/Month/year/dayOfWeek
int checkDate(char* date){
  if(
     date[2] != '/' ||
     date[5] != '/' || date[0] > '3'
  || date[0] < '0'  || date[1] < '0'
  || date[1] > '9'  || date[3] > '1'
)  {

  println("\n\nDate is invalid format...");
return 1;
}
else{
  return 0;
}
}
