#include "sensorUFSC.h"
#include <ctime>

/*************************************************************
 *                        FAKE HAL 
*************************************************************/
float HAL_FAKE::analog_read(int analog_pin){
  return 1.1;
}

int HAL_FAKE::digital_read(int digital_pin){
  return 1;
}

int HAL_FAKE::digital_write(int digital_pin){
  return 0;
}

time_t HAL_FAKE::time(){
  return std::time(0); // CUIDADO: sem o "std::" ele vira uma função recursiva!!
}


/*************************************************************
 *                        ATMEGA 
*************************************************************/
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

/*************************************************************
 *                        ESP32 
*************************************************************/
float HAL_ESP32::analog_read(int analog_pin){
  return 0.0;
}

int HAL_ESP32::digital_read(int digital_pin){
  return 1;
}

int HAL_ESP32::digital_write(int digital_pin){
  return 1;
}

time_t HAL_ESP32::time(){
  return 1;
}
