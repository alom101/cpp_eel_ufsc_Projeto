#include "sensorUFSC.h"
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


// Sensores

FakeSensor::FakeSensor(float value){
  char sensor_name[] = "FakeSensor";
  char sensor_type[] = "FakeSensor";
  set_sensor_name(sensor_name);
  set_sensor_type(sensor_type);
  _value = value;
}

Measurement FakeSensor::read(){
    return Measurement(this, _value, time(0));
  }



class AnalogReadSensor: public Sensor{
protected:
  HAL* _hal;
  int _pin;
  char _sensor_name[20] = "Analog sensor";
  char _sensor_type[20] = "Analog sensor";
public:
  AnalogReadSensor(HAL* hal, int analog_pin){
    _hal = hal;
    _pin = analog_pin;
  }

  Measurement read(){
    float value = _hal->analog_read(_pin);
    time_t now = time(0);
    return Measurement(this, value, now);
  }

};

