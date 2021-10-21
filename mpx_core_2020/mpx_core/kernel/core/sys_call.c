#include <pcb.h>
#include <sys_call.h>
u32int* sys_call(context* registers);

sys_call(context* registers){
GLOBAL PCB* cop;
context* saveOld;

if(cop == NULL){
saveOld = registers;
}
else{
  if(params.opcode == IDLE){
  saveOld = registers;
  cop->stackTop = registers;
  }
  else if(params.opcode == EXIT){
  FreePCB(cop);
  }
}

  if(isEmpty(ready) == 0 ){
    PCB* pcb = ready->head;
    RemovePCB(pcb);
    pcb->stateReady = 1;
    cop = pcb;
    return cop->stackTop;
  }
  else{
  return saveOld;
  }
}
