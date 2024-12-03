#include "config.h"
#include "sensorUFSC.h"
#include <cstdio>
#include <cstring>

// Sensor (classe abstrata)
Sensor::Sensor(){
  char sensor_name[] = "desconhecido";
  char sensor_type[] = "desconhecido";
  set_sensor_name(sensor_name);
  set_sensor_type(sensor_type);
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


// Fake Sensor
FakeSensor::FakeSensor(float value){
  char sensor_name[] = "FakeSensor";
  char sensor_type[] = "FakeSensor";
  set_sensor_name(sensor_name);
  set_sensor_type(sensor_type);
  _value = value; // valor que ele irá repetir nos testes
}

Measurement FakeSensor::read(){
    return Measurement(this, _value, time(0)); // ToDo: transferir a responsabilidade de controle de tempo para a classe HAL
  }


// Analog Sensor
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
    time_t now = time(0); // ToDo: transferir a responsabilidade de controle de tempo para a classe HAL
    return Measurement(this, value, now);
  }
