#include "sensorUFSC.h"

/*************************************************************
 *                     SENSOR (classe abstrata)
*************************************************************/
// Sensor (classe abstrata)
Sensor::Sensor(){
  char sensor_name[] = "desconhecido";
  char sensor_type[] = "desconhecido";
  set_sensor_name(sensor_name);
  set_sensor_type(sensor_type);
  _hal = 0;
}

void Sensor::set_sensor_type(char* new_type){
  strncpy(_sensor_type, new_type, SENSOR_TYPE_LEN);
}

void Sensor::set_sensor_name(char* new_name){
  strncpy(_sensor_name, new_name, SENSOR_NAME_LEN);
}

char* Sensor::sensor_type(){
  return _sensor_type;
}

char* Sensor::sensor_name(){
  return _sensor_name;
}


/*************************************************************
 *                      FAKE SENSOR
*************************************************************/
// Fake Sensor
FakeSensor::FakeSensor(HAL* hal, float value){
  char sensor_name[] = "FakeSensor";
  char sensor_type[] = "FakeSensor";
  set_sensor_name(sensor_name);
  set_sensor_type(sensor_type);
  _value = value; // valor que ele irá repetir nos testes
  _hal = hal;
}

Measurement FakeSensor::read(){
    return Measurement(this, _value, _hal->time());
}


/*************************************************************
 *                    ANALOG READ SENSOR
*************************************************************/
AnalogReadSensor::AnalogReadSensor(HAL* hal, int analog_pin){
  char sensor_name[SENSOR_NAME_LEN];
  snprintf(sensor_name, SENSOR_NAME_LEN, "Analog Sensor reading pin %d", analog_pin);
  char sensor_type[] = "Analog sensor";
  set_sensor_name(sensor_name);
  set_sensor_type(sensor_type);
  _hal = hal;
  _pin = analog_pin;
}

Measurement AnalogReadSensor::read(){
    float value = _hal->analog_read(_pin);
    time_t now = _hal->time();
    return Measurement(this, value, now);
}

/*************************************************************
 *                    DIGITAL READ SENSOR
*************************************************************/

DigitalReadSensor::DigitalReadSensor(HAL* hal, int digital_pin){
  char sensor_name[SENSOR_NAME_LEN];
  snprintf(sensor_name, SENSOR_NAME_LEN, "Digital Sensor reading pin %d", digital_pin);
  char sensor_type[] = "Digital sensor";
  set_sensor_name(sensor_name);
  set_sensor_type(sensor_type);
  _hal = hal;
  _pin = digital_pin;
}

Measurement DigitalReadSensor::read(){
  int value = _hal->digital_read(_pin);
  time_t now = _hal->time();
  return Measurement(this, value, now);
}



/*************************************************************
 *                      MPU9250 SENSOR
*************************************************************/
MPU9250Sensor::MPU9250Sensor(HAL* hal){
  char sensor_name[] = "MPU9250";
  char sensor_type[] = "MPU9250";
  set_sensor_name(sensor_name);
  set_sensor_type(sensor_type);
  _hal = hal;

}

Measurement MPU9250Sensor::read(){
    return Measurement(this, _value, _hal->time());
}

