#include <string.h>
#include "mpx_supt.h"
#include "print.h"
#include "date.h"
#include <core/io.h>
#include "bcdConversion.h

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

void getdate(){
char date[12] = "0/00/00/0000";

//dayofweek
outb(0x70, 0x06);
BCDtoStr(inb(0x71), date);

//Month
outb(0x70, 0x08);
BCDtoStr(inb(0x71), &date[2]);

//dayOfMonth
outb(0x70, 0x07);
 BCDtoStr(inb(0x71), &date[5]);

//year
outb(0x70, 0x09);
BCDtoStr(inb(0x71), &date[8]);

print("Current Date formatted dayOfWeek/Month/dayOfMonth/Year is: ");
println(date);
return;

}


 void setdate(){
   char cmdBuffer[100];
   int bufferSize;
   memset(cmdBuffer, '\0', 100);
   bufferSize = 99;
   print("Enter a date in the form dayOfWeek/month/dayOfMonth/Year");
   print("For day of week: Sunday = 1 -- Saturday = 7 ");
   print("Example date could be 5/10/30/1999 - or Thursday, October 30th 1999");
  sys_req(READ,DEFAULT_DEVICE,cmdBuffer,&bufferSize);
  char date[12];
  strcpy(date, cmdBuffer);
  int count=0;
  while(count <12){
    count++;

  }

  if(date[1] != '/' && date[4] != '/' && date[7] != '/'){
    print("incorrecto formatto dumbasso");
  }

cli();


//dayofweek
outb(0x70, 0x06);
outb(0x71, StrtoBCD(date));

//month
outb(0x70, 0x08);
outb(0x71, StrtoBCD(&date[2]));

//dayOfMonth
outb(0x70, 0x07);
outb(0x71, StrtoBCD(&date[5]));

//year
outb(0x70, 0x09);
outb(0x71, StrtoBCD(&date[8]));

print("date has been set in the form dayOfWeek/Month/dayOfMonth/Year to: ");
println(date);
sti();
}
