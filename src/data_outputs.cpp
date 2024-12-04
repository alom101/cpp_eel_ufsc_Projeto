#include "sensorUFSC.h"



/*************************************************************
 *                      PRINT OUTPUT
*************************************************************/
PrintOutput::PrintOutput(){
};

void PrintOutput::save(Measurement data){
  time_t t = data.timestamp(); 
  printf("Medida %f feita em %s do tipo %s em %s", data.value(), data.sensor_name(), data.sensor_type(), ctime(&t));
}

/*************************************************************
 *                      SD CARD OUTPUT (ToDo)
*************************************************************/
SDCardOutput::SDCardOutput(){
}

void SDCardOutput::save(Measurement data){

}

/*************************************************************
 *                      DIGITAL PIN OUTPUT (ToDo)
*************************************************************/
DigitalPinOutput::DigitalPinOutput(HAL* hal, int digital_pin){
  _hal = hal;
  _pin = digital_pin;
}

void DigitalPinOutput::save(Measurement data){
  if(data.value() == 0.0){
    _hal->digital_write(LOW, _pin);
  } else {
    _hal->digital_write(HIGH, _pin);
  }
}
