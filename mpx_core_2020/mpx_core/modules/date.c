#include <string.h>
#include "mpx_supt.h"
#include "print.h"
#include "date.h"
#include <core/io.h>
#include "bcdConversion.c"

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


 void setdate(char* date){
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
