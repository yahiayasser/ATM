#include "ATM.h"

void ATM_MC_Init(void){
    IO_INIT;
    COM_INIT;
    //TIMERS_INIT;
}

void ATM_HW_Init(void){
	OUTPUT_MODULES_INIT;
}
