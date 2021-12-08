#include "serial.h"
//#include "dcb.h"
#include <core/serial.h>
#include <core/io.h>
#include <core/tables.h>
#include <string.h>
#include "print.h"
#include "iocb.h"

u32int dev = COM1;
int level = 4;

struct dcb serial_dcb ={
    .ring_s = sizeof(*(serial_dcb.ring)/sizeof(unsigned char))
};
iocb *serial_iocb;

u32int original_idt_entry;

//diables by loading 0 into interupt enable register
void disable_interupt(){
  outb(dev + 1, 0x0);
}

//enable by loading 0x01 int enable register
void enable_interupt(){
  outb(dev + 1, 0x01);
}

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

void output_h(){
  if(serial_dcb.status != WRITING){
      return;
  }
  if(serial_dcb.out_x < serial_dcb.out_s){
      outb(dev, *(serial_dcb.out));//store in out index
      serial_dcb.out =serial_dcb.out + 1;
      (serial_dcb.out_x)++;
      return;
  }
  //otherwise all characters have been transered aka Doing NOTHING
  else{
    serial_dcb.status = NOTHING;
    serial_iocb->status = NOTHING;
    //set event flag
    serial_iocb->events = 1;
    //count equals index????? maybe
    (serial_dcb.out_count) = serial_dcb.out_x;
//disable interupts, clear 1  bit in inturupt enable register
//
    outb(COM1 + 1, (inb(COM1 + 1) & ~0x02));
    return;
  }


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
    output_h();
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
  if(!serial_dcb.open){
    return CLOSE_PORT_NOT_OPEN;
  }
  serial_dcb.open = 0;
  disable_interupt();
  int pic_mask = inb(0x21) | 0x10;
  outb(0x21,pic_mask);
  enable_interupt();
  //modem and
  outb(dev + 6, 0);
  outb(dev + 1, 0);
  //restore originial saved interupt vector???? idk how
  return 0;
}

// int com_read(char *buf_p, int *count_p){
//   //need to validate the params
//
//   if(serial_dcb.open == 0){
//     return READ_PORT_NOT_OPEN -301;
//   }
//   if(serial_dcb.status != NOTHING){
//   return READ_DEVICE_BUSY -304;
//   }
//   //initialize the input buffers current index, size, and status
//   serial_dcb.in_x = serial_dcb.ring_inx;
//   serial_dcb.in_s = (serial_dcb.ring_s - serial_dcb.out_s);
//   if(serial_dcb.ring_s >= count_p){
//     //do i need to read in the ring buffer or just return 0
//     return 0;
//   }
//   serial_dcb.status = READING;
//
//   //somehow clear callers event flag below -- proly not right
//   serial_dcb.events = 0; //null? and buf_p is not a dcb im lost.
//
//   //copy chars -- need to disable input interupts or all interupts
//   int i = 0;
//   while(serial_dcb.ring[i] != NULL && serial_dcb.ring[i] <= count_p){
//     //disable ints
//     outb(dev + 1, 0b00000000);
//
//     buf_p = serial_dcb.ring[i]; //this cant be right
//
//     //detect if a CR (enter) code has been found??
//     if(serial_dcb.ring[i] == CR){
//       break;
//     }
//     serial_dcb.ring[i] = NULL;
//     i++;
//   }
//   serial_dcb.status = NOTHING;
//   serial_dcb.events = 1;
//   //return the actual count?
//   return 0;
// }

int com_write(char* buf_p, int* count_p)
{
  if (serial_dcb.open == 0)
  {
    return WRITE_PORT_NOT_OPEN;
  }

  // Need to validate the parameters...?
  if (buf_p == NULL)
  {
    return WRITE_INVALID_BUFFER_ADDR;
  }

  if (count_p == NULL || count_p <= 0)
  {
    return WRITE_INVALID_COUNT;
  }

  if(serial_dcb.status != NOTHING)
  {
    return WRITE_DEVICE_BUSY;
  }

  serial_dcb.status = WRITING;
  serial_dcb.out_x=(int)buf_p;
  serial_dcb.out_s=(int)count_p;
  serial_iocb.status = WRITING;

  serial_dcb.events = 0;

  // Get first character from requestor's buffer and store it into output buffer.
  //char input = inb(buf_p)
  //outb(serial_dcb.out,input);

  outb(dev, serial_dcb.out_x);
  serial_dcb.out_x = serial_dcb.out_x + 1;


  // i think this is right pulled from emilys output_h
  //outb(dev, *(serial_dcb.out));//store in out index
  //serial_dcb.out =serial_dcb.out + 1

  // Enable write interrupts
  //outb(dev +1, 0x02 | inb(0x02));
  int interuptE = inb(dev + 1);
  interuptE = interuptE | 0x02;
  outb(dev + 1, interuptE);

  return 0;
}
// for iocb iqueue
void enqueue (iqueue *q, iocb *iocb){
  //if nothingg is in the iqueue yet, set the head and tail to the new pcb
  if(q->count == 0){

    q->head = iocb;
    q->tail = iocb;
  }

  else{
    //set the tail's next element equal to the pcb, and the pcb's previous element equal to the tail,
    // and  finally the tail equal to the  pcb
    q->tail->next = iocb;
    iocb->previous = q->tail;
    q->tail = iocb;
  }
  q->count++;
}
iocb* dequeue(iqueue *q){
  if(q->count == 0){
    return NULL;
  }
  else if(q->count == 1){
    iocb *iocb = q->head;
    q->head = NULL;
    q->tail = NULL;
    q->count = 0;
    return iocb;
  }
    iocb *iocb = q->head;
    q->head = q->head->next;
    q->count = q->count - 1;
    return iocb;

}
