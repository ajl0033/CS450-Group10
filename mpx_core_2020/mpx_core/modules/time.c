#include <string.h>
#include "mpx_supt.h"
#include "print.h"
#include "time.h"
#include "bcdConversion.h"
#include <core/io.h>

//needs fixing just a start
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


  print("Current time: ");
  println(time);
  return 0;
}
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
int check_time_str(char* time_str){

if(strlen(time_str)> 8 ||
   time_str[0]  <  '0' || time_str[0] > '2' ||
   time_str[1]  <  '0' || time_str[1] > '9' ||
   time_str[2]  != ':' ||
   time_str[3]  <  '0' || time_str[3] > '6' ||
   time_str[4]  <  '0' || time_str[4] > '9' ||
   time_str[5]  != ':' ||
   time_str[6]  <  '0' || time_str[6] > '6' ||
   time_str[7]  <  '0' || time_str[7] > '9'){
  println("that time is invalid dumb@$$");
  return 1;
}

else{
  return 0;
  }
}
