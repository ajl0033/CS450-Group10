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

int com_close(void)
{
  return 0;
}

int com_read(char *buf_p, int *count_p){
  //need to validate the params
  //error checking for port and status below
  if(serial_dcb.open == 0){
    return READ_PORT_NOT_OPEN -301;
  }
  if(serial_dcb.status != IDLE){
    return READ_DEVICE_BUSY -304;
  }
  //initialize the input buffers current index, size, and status
  serial_dcb.in_x = serial_dcb.ring_inx;
  serial_dcb.in_s = (serial_dcb.ring_s - serial_dcb.out_s);
  if(serial_dcb.ring_s >= count_p){
    //do i need to read in the ring buffer or just return 0
    return 0;
  }
  serial_dcb.status = READING;

  //somehow clear callers event flag below -- proly not right
  buf_p.events = 0; //null? and buf_p is not a dcb im lost.

  //copy chars -- need to disable input interupts or all interupts
  int i = 0;
  while(serial_dcb.ring[i] != NULL && serial_dcb.ring[i] <= count_p){
    //disable ints
    outb(dev + 1, 0b00000000);

    buf_p = serial_dcb.ring[i]; //this cant be right

    //detect if a CR (enter) code has been found??
    if(serial_dcb.ring[i] == CR){
      break;
    }
    serial_dcb.ring[i] = NULL;
    i++;
  }

  serial_dcb.status = NOTHING;
  serial_dcb.events = 1;
  //return the actual count?

}

int com_write(char* buf_p, int* count_p)
{
  if (serial_dcb.open == 0)
  {
    return WRITE_PORT_NOT_OPEN;
  }

  // Need to validate the parameters
  /*
  if (buf_p == invalid)
  {
    return WRITE_INVALID_BUFFER_ADDR;
  }

  if (count_p == invalid)
  {
    return WRITE_INVALID_COUNT;
  }
  */

  if(serial_dcb.status != NOTHING)
  {
    return WRITE_DEVICE_BUSY;
  }

  serial_dcb.status = WRITING;
  serial_dcb.out = buf_p;
  serial_dcb.out_x = 0;
  serial_dcb.out_s = count_p;

  serial_dcb.events = 0;


  return 0;
}
