#ifndef SENSORUFSC_H
#define SENSORUFSC_H

#include <ctime>
#include "config.h"

class Sensor;
class DataOutput;
class Measurement;
class HAL;
// class MeasurementStrategy;


// Interface abstrata para sensores
class Sensor{
protected:
  char _sensor_name[SENSOR_NAME_LEN];
  char _sensor_type[SENSOR_TYPE_LEN];
  void set_sensor_type(char* new_type);
  Sensor();
public:
  // CORE
  virtual Measurement read() = 0;

  // METADATA
  void set_sensor_name(char* new_name);
  char* sensor_type();
  char* sensor_name();
};

class FakeSensor: public Sensor{
protected:
  float _value;
public:
  FakeSensor(float fixed_return_value);
  Measurement read();
};

class AnalogReadSensor: public Sensor{
protected:
  HAL* _hal;
  int _pin;
public:
  AnalogReadSensor(HAL* hal, int analog_pin);
  Measurement read();
};


// Interface abstrata para saida de dados
class DataOutput{
public:
  virtual int save(Measurement data) = 0;
};



// Realiza medidas e as salva de forma periódica(talvez generalizar essa parte por um objeto MeasurementStrategy ou algo assim)
class Scheduler{
public:
  Scheduler(Sensor* sensor, DataOutput* output, float sample_rate);
  int update();
};


// Encapsula a medida, para facilitar alterações. Também disponibiliza alguns metadados.
class Measurement{
protected:
  Sensor* _sensor = 0;
  time_t _timestamp;
  float _value;
public:
  Measurement(Sensor* sensor, float value, time_t timestamp);
  float value();
  time_t timestamp();
  // METADATA
  char* sensor_type();
  char* sensor_name();
};


// Interface para interação com o hardware
class HAL{
public:
  virtual float analog_read(int analog_pin);
  virtual int digital_read(int digital_pin);
  virtual int digital_write(int digital_pin);
};


#endif // !SENSORUFSC_H
