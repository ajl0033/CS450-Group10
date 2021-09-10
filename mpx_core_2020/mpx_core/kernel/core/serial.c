/*
  ----- serial.c -----

  Description..: Contains methods and variables used for
    serial input and output.
*/

#include <stdint.h>
#include <string.h>

#include <core/io.h>
#include <core/serial.h>

#include "modules/print.h"

#define NO_ERROR 0

// Active devices used for serial I/O
int serial_port_out = 0;
int serial_port_in = 0;

/*
  Procedure..: init_serial
  Description..: Initializes devices for user interaction, logging, ...
*/
int init_serial(int device)
{
  outb(device + 1, 0x00); //disable interrupts
  outb(device + 3, 0x80); //set line control register
  outb(device + 0, 115200/9600); //set bsd least sig bit
  outb(device + 1, 0x00); //brd most significant bit
  outb(device + 3, 0x03); //lock divisor; 8bits, no parity, one stop
  outb(device + 2, 0xC7); //enable fifo, clear, 14byte threshold
  outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
  (void)inb(device);      //read bit to reset port
  return NO_ERROR;
}

/*
  Procedure..: serial_println
  Description..: Writes a message to the active serial output device.
    Appends a newline character.
*/
int serial_println(const char *msg)
{
  int i;
  for(i=0; *(i+msg)!='\0'; i++){
    outb(serial_port_out,*(i+msg));
  }
  outb(serial_port_out,'\r');
  outb(serial_port_out,'\n');
  return NO_ERROR;
}

/*
  Procedure..: serial_print
  Description..: Writes a message to the active serial output device.
*/
int serial_print(const char *msg)
{
  int i;
  for(i=0; *(i+msg)!='\0'; i++){
    outb(serial_port_out,*(i+msg));
  }
  if (*msg == '\r') outb(serial_port_out,'\n');
  return NO_ERROR;
}

/*int (*student_read)(char *buffer, int *count);
  Procedure..: set_serial_out
  Description..: Sets serial_port_out to the given device address.
    All serial output, such as that from serial_println, will be
    directed to this device.
*/
int set_serial_out(int device)
{
  serial_port_out = device;
  return NO_ERROR;
}

/*
  Procedure..: set_serial_in
  Description..: Sets serial_port_in to the given device address.
    All serial input, such as console input via a virtual machine,
    QEMU/Bochs/etc, will be directed to this device.
*/
int set_serial_in(int device)
{
  serial_port_in = device;
  return NO_ERROR;
}

/*
 * Gathers keyboard input from the user and passes it into the command buffer
 which is stored as a char pointer.
 * It validates each keystroke including all alphanumeric characters, backslash,
 forwardslash, comma, and period.  It also handles special keys such as backspace,
 delete, the home and end key, and the arrow keys.
 *
 * @param - buffer (char-pointer): the data that is stored in the command buffer
 (usually empty)
 * @param - count (integer-pointer): the value of the size of the buffer
 (this is the value that remains unchanged and returns)
 *
 * @return (integer-pointer): the value of the size of the buffer
*/
int *polling(char *buffer, int *count){
// insert your code to gather keyboard input via the technique of polling.
// You must validat each key and handle special keys such as delete, back space, and
// arrow keys
int counter = 0;
int index = 0;
print("user@MPX:~/$ ");
while(1)
{

  if (inb(COM1+5) & 1)
  {
    // Assign character input to letter
    char letter = inb(COM1);


    // println("\n\n");
    // print("===");
    // print(&letter);
    // print("===");
    // println("\n\n");


    // Check if enter is pressed
    // If enter is pressed, return count
    if (letter == '\n' || letter == '\r')
    {
      return count;
    } // Check if backspace is pressed
    else if (letter == 127)
    {
      if (counter == 0)
      {
        continue;
      }
      else if (index == 0)
      {
        int i;
        for (i = 0; i < counter+1; i++)
        {
          buffer[i] = buffer[i+1];
        }
        counter--;
        print("\33[2K\ruser@MPX:~/$ ");
        print(buffer);
        int j;
        int diff = counter-index;
        for(j = 0; j < diff; j++)
        {
          print("\033[1D");
        }
        continue;
      }
      else
      {
        int i;
        for (i = 0; i < counter; i++)
        {
          if (i >= index-1)
          {
            buffer[i] = buffer[i+1];
          }
        }
        // Decrement counter and index
        // Print buffer
        counter--;
        index--;
        print("\33[2K\ruser@MPX:~/$ ");
        print(buffer);
        int j;
        int diff = counter-index;
        for(j = 0; j < diff; j++)
        {
          print("\033[1D");
        }
        continue;
      }
    }  // Check arrow keys
    else if (letter == '[')
    {
      int checker = 1;
      while(checker == 1)
      {
        if (inb(COM1+5) & 1)
        {
          char letter2 = inb(COM1);
          // delete key
          if (letter2 == '3')
          {
            if (counter == 0)
            {
              continue;
            }
            else if (index == 0)
            {
              int i;
              for (i = 0; i < counter+1; i++)
              {
                buffer[i] = buffer[i+1];
              }
              counter--;
              print("\33[2K\ruser@MPX:~/$ ");
              print(buffer);
              int j;
              int diff = counter-index;
              for(j = 0; j < diff; j++)
              {
                print("\033[1D");
              }
              continue;
            }
            else
            {
              int i;
              for (i = 0; i < counter; i++)
              {
                if (i >= index-1)
                {
                  buffer[i] = buffer[i+1];
                }
              }
              // Decrement counter and index
              // Print buffer
              counter--;
              index--;
              print("\33[2K\ruser@MPX:~/$ ");
              print(buffer);
              int j;
              int diff = counter-index;
              for(j = 0; j < diff; j++)
              {
                print("\033[1D");
              }
              continue;
            }
            checker = 0;
          }
          // home key
          if (letter2 == 'H')
          {
            checker = 0;
            int j;
            for(j = 0; j < index; j++)
            {
              print("\033[1D");
            }
            index = 0;
          }
          // end key
          if (letter2 == 'F')
          {
            checker = 0;
            int j;
            int diff = counter-index;
            for(j = 0; j < diff; j++)
            {
              print("\033[1C");
            }
            index = counter;
          }
          // up arrow
          if (letter2 == 'A')
          {
            checker = 0;
          }
          // down arrow
          else if (letter2 == 'B')
          {
            checker = 0;
          } // left arrow
          else if (letter2 == 'D')
          {
            if (counter > 0)
            {
              if (index > 0)
              {
                index--;
                checker = 0;
                print("\033[1D");
              }
              else
              {
                checker = 0;
                print("\033[1D");
              }
            }
            else
            {
              checker = 0;
              print("\033[1D");
            }
          }
            // right arrow
            else if (letter2 == 'C')
            {
              if (index < counter)
              {
                index++;
                checker = 0;
                print("\033[C");
              }
              else
              {
                checker = 0;
                print("\033[C");
              }
            }
            else
            {
              checker = 0;
            }
          }
        }
      continue;
    } // Check for letter or number
    else if ((letter >= 97 && letter <= 122) || (letter >= 44 && letter <= 59) || (letter >= 65 && letter <= 90) || (letter == 92))
    {
      if (index < counter)
      {
        int i;
        for(i = counter; i > index; i--)
        {
          buffer[i] = buffer[i-1];
        }
      }
      buffer[index] = letter;

      index++;
      counter++;

      // Print buffer
      print("\33[2K\ruser@MPX:~/$ ");
      print(buffer);
      int j;
      for(j = counter; j > index; j--)
      {
        print("\033[1D");
      }
      continue;
    }
  }
}
return count;
}
