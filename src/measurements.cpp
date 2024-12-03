#include "sensorUFSC.h"


Measurement::Measurement(Sensor* sensor, float value, time_t timestamp){
  _sensor = sensor;
  _value = value;
  _timestamp = timestamp;
}

float Measurement::value(){
  return _value;
}

time_t Measurement::timestamp(){
  return _timestamp;
}

char* Measurement::sensor_name(){
  return _sensor->sensor_name();
}

char* Measurement::sensor_type(){
  return _sensor->sensor_type();
}
