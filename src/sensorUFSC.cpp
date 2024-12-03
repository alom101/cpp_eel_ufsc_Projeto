#include "sensorUFSC.h"
#include <ctime>


// Measurement
Measurement::Measurement(Sensor* sensor, float value, time_t timestamp){
  _sensor = sensor;
  _value = value;
  _timestamp = timestamp;
}

char* Measurement::sensor_name(){
  return _sensor->sensor_name();
}

char* Measurement::sensor_type(){
  return _sensor->sensor_type();
}

// Sensor (classe abstrata)
char* Sensor::sensor_type(){
  return _sensor_type;
}

char* Sensor::sensor_name(){
  return _sensor_name;
}

// Sensores

class FakeSensor: public Sensor{
protected:
  const float FIXED_VALUE = 1.1111;
  char _sensor_name[20] = "Fake sensor";
  char _sensor_type[20] = "Fake sensor";
public:
  Measurement read(){
    return Measurement(this, FIXED_VALUE, time(0));
  }
};

class AnalogReadSensor: public Sensor{
protected:
  HAL* _hal;
  int _pin;
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

