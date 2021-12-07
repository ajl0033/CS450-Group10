#ifndef _SERIAL_DRIVER_H_
#define _SERIAL_DRIVER_H_

#include "dcb.h"


void set_int(int bit, int on);

void input_h();

void top_handler();

int com_open(int baud_rate);

int com_close(void);

int com_read(char* buf_p, int* count_p);

int com_write(char* buf_p, int* count_p);

#endif
