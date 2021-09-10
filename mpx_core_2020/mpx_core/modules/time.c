#include <string.h>
#include "mpx_supt.h"
#include "print.h"
#include "time.h"
#include "bcdConversion.h"
#include <core/io.h>

/*
get time has no arguements
irrelvantly returns 0
prints the time that was accessed through the outb function
calls bcdtoStr on the time to convert from BCD to a char and place it in the time char array
*/
int gettime(){
  //testing output
char time[9]= "00:00:00";


  //hours
  outb(0x70, 0x04);
  BCDtoStr(inb(0x71), &time[0]);


  //minutes
  outb(0x70, 0x02);
  BCDtoStr(inb(0x71), &time[3]);

  //seconds
  outb(0x70, 0x00);
  BCDtoStr(inb(0x71), &time[6]);


  print("\n\nCurrent Time (HH:MM:SS): ");
  println(time);
  return 0;
}

/*
set time has the time char array pointer as an arguement
irrelvantly return 0 or 1 if the time is invalid
the time has aleardy been inputted after printing a prompt in the command handler
calls check_time_str to make sure the time entered was valid
sets the time using the outB and StrtoBCD function to convert the char to a BCD

*/
int settime(char* time){
  if(check_time_str(time)){
    return 1;
  }else{
    cli();


    //hours
    outb(0x70, 0x04);
    outb(0x71, StrtoBCD(&time[0]));

    //minutes
    outb(0x70, 0x02);
    outb(0x71, StrtoBCD(&time[3]));

    //seconds
    outb(0x70, 0x00);
    outb(0x71, StrtoBCD(&time[6]));

    print("\nTime has been set to: ");
    println(time);
    sti();
    return 0;
  }

}
/*
check_time_str recieves the time char array pointer as an arguement
makes sure the time is of valid length and valid format in military time
returns 0 if the time is valid and 1 if the time is invalid
if 0 is returned the settime function continues if 1 is returned a invalid format message is returned

*/
int check_time_str(char* time_str){
if (time_str[0] == '2')
{
  if (time_str[1] > '3')
  {
    print("\033[31m");
    println("\nTime is invalid format...");
    print("\033[37m");
    return 1;
  }
}
if(strlen(time_str)> 8 ||
   time_str[0]  <  '0' || time_str[0] > '2' ||
   time_str[1]  <  '0' || time_str[1] > '9' ||
   time_str[2]  != ':' ||
   time_str[3]  <  '0' || time_str[3] > '5' ||
   time_str[4]  <  '0' || time_str[4] > '9' ||
   time_str[5]  != ':' ||
   time_str[6]  <  '0' || time_str[6] > '5' ||
   time_str[7]  <  '0' || time_str[7] > '9'){
  print("\033[31m");
  println("\nTime is invalid format...");
  print("\033[37m");
  return 1;
}

else{
  return 0;
  }
}
