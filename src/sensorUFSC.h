#ifndef SENSORUFSC_H
#define SENSORUFSC_H

#include "config.h"
#include <ctime>

class Sensor;
class DataOutput;
class Measurement;
// class MeasurementStrategy;


// Interface abstrata para sensores
class Sensor{
public:
  // CORE
  virtual Measurement read() = 0;

  // METADATA
  virtual char* sensor_type();
  virtual char* sensor_name();
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
  Sensor* from_sensor = 0;
public:
  float value();
  time_t timestamp();
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