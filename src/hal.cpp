#include "sensorUFSC.h"


/*************************************************************
 *                        ATMEGA 
*************************************************************/

// #ifdef TARGET_ATMEGA
//
// #endif // TARGET_ATMEGA

float HAL_ATMEGA::analog_read(int analog_pin){
  return 0.0;
}

int HAL_ATMEGA::digital_read(int digital_pin){
  return 1;
}

int HAL_ATMEGA::digital_write(int digital_pin){
  return 1;
}

time_t HAL_ATMEGA::time(){
  return 1;
}
