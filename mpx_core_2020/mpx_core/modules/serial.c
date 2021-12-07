#include "serial.h"
#include "dcb.h"
#include <core/serial.h>
#include <core/io.h>
#include <core/tables.h>
#include <string.h>
#include "print.h"

u32int dev = COM1;
int level = 4;

struct dcb serial_dcb ={
    .ring_s = sizeof(*(serial_dcb.ring)/sizeof(unsigned char))
};

u32int original_idt_entry;

void set_int(int bit, int on){
  if(on == 1){
    outb(dev + 1, inb(dev + 1) | (1<<bit));

  }
  else{
    outb(dev + 1, inb(dev + 1) & ~(1<<bit));
  }
}
void input_h(){
  char i = inb(dev);
  outb(dev, i);
}

void top_handler(){
  if (serial_dcb.open == 1) {
    cli();
    int type = inb(dev + 2);
    int bit1 = type>>1 & 1;
    int bit2 = type>>2 & 1;
  //  klogv("Int");
  //  char in = inb(dev);
  //  outb(dev, in);
  if(!bit1 && !bit2){
    //modem
    inb(dev + 6);
  }
  else if(bit1 && !bit2){
    //outputhandler
  }
  else if(!bit1 && bit2){
    input_h();
  }
  else if(bit1 && bit2){
    inb(dev + 5);
  }
    sti();

  }
  //klogv("Disable");

outb(0x20, 0x20);
}


int com_open(int baud_rate){
  //Error Checking
  //baud_rate valid
  //port is NOT open
  cli();

  serial_dcb.open = 1;
  serial_dcb.events = 1;
  serial_dcb.status = NOTHING;

  original_idt_entry = idt_get_gate(0x24);
  idt_set_gate(0x24, (u32int) top_handler, 0x08, 0x8e);

  long brd = 115200/(long) baud_rate;

  //disable ints
  outb(dev + 1, 0b00000000);

  //set time control register
  outb(dev + 3, 0b00000000);
    //LSB baud_rate
  outb(dev + 0, brd);

    //MSB baud_rate
  outb(dev +1, brd >> 8);

    //lock devisor
  outb(dev + 3, 0b00000011);

    //Enable FIFO, clear, 14 byte threshold
    outb(dev + 2, 0b11000111);

    //enable PIC level
    outb(0x21, inb(0x21) & ~(1<<level));

    outb(dev + 1, 0b00000001);
    (void) inb(dev);

    sti();

    return 0;

}
