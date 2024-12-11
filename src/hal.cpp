#include "sensorUFSC.h"

/*************************************************************
 *                        FAKE HAL 
*************************************************************/
time_t __time(time_t *t){
  return time(t);
}

float HAL_FAKE::analog_read(int analog_pin){
  return 1.1;
}

int HAL_FAKE::digital_read(int digital_pin){
  return 0;
}

int HAL_FAKE::digital_write(int value, int digital_pin){
  return 0;
}

time_t HAL_FAKE::time(){
  return __time(0); // CUIDADO: sem o "std::" ele vira uma função recursiva!!
}


/*************************************************************
 *                        ATMEGA 
*************************************************************/
HAL_ATMEGA::HAL_ATMEGA(){

}

float HAL_ATMEGA::analog_read(int analog_pin){
// ToDo
  return 0.0;
}

int HAL_ATMEGA::digital_read(int digital_pin){
  // DDRB = DDRB|(1<<digital_pin);
  // return (PORTB>>digital_pin)&0x01;
    return 1;
}

int HAL_ATMEGA::digital_write(int value, int digital_pin){
  // DDRB = DDRB|(1<<digital_pin);
  // PORTB &= (1<<digital_pin);
  return 1;
}

time_t HAL_ATMEGA::time(){
  return 1;
}

/*************************************************************
 *                        ESP32 (ToDo)
*************************************************************/

HAL_ESP32::HAL_ESP32(){
  #ifdef TARGET_ESP32
  ESP_ERROR_CHECK(i2c_master_init());
  #endif //TARGET_ESP32
}

float HAL_ESP32::analog_read(int analog_pin){
  return 0.0;
}

int HAL_ESP32::digital_read(int digital_pin){
  return 1;
}

int HAL_ESP32::digital_write(int value, int digital_pin){
  return 1;
}

time_t HAL_ESP32::time(){
  return 1;
}
