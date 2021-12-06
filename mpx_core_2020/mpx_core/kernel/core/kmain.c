/*
  ----- kmain.c -----

  Description..: Kernel main. The first function called after
      the bootloader. Initialization of hardware, system
      structures, devices, and initial processes happens here.

      Initial Kernel -- by Forrest Desjardin, 2013,
      Modifications by:    Andrew Duncan 2014,  John Jacko 2017
      				Ben Smith 2018, and Alex Wilson 2019
*/

/////////// FOR PHASE 1 TESTING ///////////
//  Line 43:     MEM_MODULE -> MODULE_R4
//  Line 99-105: Comment
//  Uncomment code in comhand (607-685)


#include <stdint.h>
#include <string.h>
#include <system.h>

#include <core/io.h>
#include <core/serial.h>
#include "modules/serial.h"
#include <core/tables.h>
#include <core/interrupts.h>
#include <mem/heap.h>
#include <mem/paging.h>

#include "modules/mpx_supt.h"

#include "modules/CommandHandler.h"

#include "modules/print.h"

#include "modules/memoryblocks.h"


void kmain(void)
{
   extern uint32_t magic;
   // Uncomment if you want to access the multiboot header
   // extern void *mbd;
   // char *boot_loader_name = (char*)((long*)mbd)[16];

   mpx_init(MEM_MODULE);
   // 0) Initialize Serial I/O
   // functions to initialize serial I/O can be found in serial.c
   // there are 3 functions to call
   init_serial(COM1);
   set_serial_in(COM1);
   set_serial_out(COM1);


   klogv("Starting MPX boot sequence...");
   klogv("Initialized serial I/O on COM1 device...");

   // 1) Initialize the support software by identifying the current
   //     MPX Module.  This will change with each module.
   // you will need to call mpx_init from the mpx_supt.c

   // 2) Check that the boot was successful and correct when using grub
   // Comment this when booting the kernel directly using QEMU, etc.
   if ( magic != 0x2BADB002 ){
     //kpanic("Boot was not error free. Halting.");
   }

   // 3) Descriptor Tables -- tables.c
   //  you will need to initialize the global
   // this keeps track of allocated segments and pages
   klogv("Initializing descriptor tables...");
   init_gdt();
   init_idt();


    // 4)  Interrupt vector table --  tables.c
    // this creates and initializes a default interrupt vector table
    // this function is in tables.c

    klogv("Interrupt vector table initialized!");
    init_irq();
    sti();


   // 5) Virtual Memory -- paging.c  -- init_paging
   //  this function creates the kernel's heap
   //  from which memory will be allocated when the program calls
   // sys_alloc_mem UNTIL the memory management module  is completed
   // this allocates memory using discrete "pages" of physical memory
   // NOTE:  You will only have about 70000 bytes of dynamic memory
   //
   klogv("Initializing virtual memory...");
   init_paging();

   ///////////////////////////////////////////////////////
   ////////////////// CODE FOR R5 ////////////////////////
   ///////////////////////////////////////////////////////

   initialize_heap(50000);
   sys_set_malloc(allocate_memory);
   sys_set_free(free_memory);

   if (IsEmpty() == 0) {
     println("\nERROR: Heap is not empty immediately after initialization");
   }

   ///////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////

   // 6) Call YOUR command handler -  interface method
   klogv("Transferring control to commhand...");
   // char buffer[100];
   // int count = 1;
   print("\033[37m");


/// ONLY FOR TESTING
//com_open(1200);

i//nt a=1;
w//hile(1){
//(void) a;
//}

   // Would add comhand idle to ready queue, but do not know how to store functions in the struct
   // sys_req(IDLE, DEFAULT_DEVICE, NULL, NULL);
   //
   //
  CreatePCB("comhand", 0, 9);
	PCB* new_pcb = FindPCB("comhand");
	context* cp = (context *)(new_pcb->stackTop);
	memset (cp, 0, sizeof(context));
	cp->fs = 0x10;
	cp->gs = 0x10;
	cp->ds = 0x10;
	cp->es = 0x10;
	cp->cs = 0x8;
	cp->ebp = (u32int)( new_pcb->stack );
	cp->esp = (u32int)( new_pcb->stackTop );
	cp->eip = (u32int) comhand;
	cp->eflags = 0x202;

  CreatePCB("idle", 0, 0);
  new_pcb = FindPCB("idle");
  cp = (context *)(new_pcb->stackTop);
  memset (cp, 0, sizeof(context));
  cp->fs = 0x10;
  cp->gs = 0x10;
  cp->ds = 0x10;
  cp->es = 0x10;
  cp->cs = 0x8;
  cp->ebp = (u32int)( new_pcb->stack );
  cp->esp = (u32int)( new_pcb->stackTop );
  cp->eip = (u32int) idle;
  cp->eflags = 0x202;
   //comhand();

   yield();

   print("\033[0m");
   //intcomhand();
   println("");
   // 7) System Shutdown on return from your command handler

   klogv("Starting system shutdown procedure...");

   /* Shutdown Procedure */
   klogv("Shutdown complete. You may now turn off the machine. (QEMU: C-a x)");
   hlt();
}
