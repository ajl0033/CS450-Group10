#ifndef _SERIAL_DRIVER_H_
#define _SERIAL_DRIVER_H_

//#include "dcb.h"
#include "iocb.h"

#define OPEN_INVALID_EVENT_FLAG -101
#define OPEN_INVALID_BAUD_RATE -102
#define OPEN_PORT_IS_OPEN -103
#define CLOSE_PORT_NOT_OPEN -201
#define READ_PORT_NOT_OPEN -301
#define READ_INVALID_BUFFER_ADDR -302
#define READ_INVALID_COUNT -303
#define READ_DEVICE_BUSY -304
#define WRITE_PORT_NOT_OPEN -401
#define WRITE_INVALID_BUFFER_ADDR -402
#define WRITE_INVALID_COUNT -403
#define WRITE_DEVICE_BUSY -404

// Returns the device control block associated with the serial port
// struct dcb* com_get_dcb();
void disable_interupt();

void enable_interupt();

//void set_int(int bit, int on);

void input_h();

void top_handler();

int com_open(int baud_rate);

int com_close(void);

int com_read(char* buf_p, int* count_p);

int com_write(char* buf_p, int* count_p);

void enqueue( iqueue *q, iocb *iocb);

iocb* dequeue(iqueue *q);

#endif
