#ifndef SENSORUFSC_H
#define SENSORUFSC_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

class Sensor;
class DataOutput;
class Measurement;
class HAL;
// class MeasurementStrategy;

#define LOW 0
#define HIGH 1

#ifdef TARGET_FAKE
#define HAL_DEFAULT HAL_FAKE
#endif // TARGET_FAKE

#ifdef TARGET_ESP32
#include "targets/esp32.h"
#define HAL_DEFAULT HAL_ESP32
#endif // TARGET_ESP32

#ifdef TARGET_ATMEGA
#include "targets/atmega.h"
#define HAL_DEFAULT HAL_ATMEGA
#endif // TARGET_ATMEGA



/*************************************************************
 *                    SENSORES
*************************************************************/
// Interface abstrata para sensores
class Sensor{
protected:
  char _sensor_name[SENSOR_NAME_LEN];
  char _sensor_type[SENSOR_TYPE_LEN];
  HAL* _hal = 0;
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

// Simula um sensor. Realiza sempre a mesma medida
class FakeSensor: public Sensor{
protected:
  float _value;
public:
  FakeSensor(HAL* hal, float fixed_return_value);
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

class DigitalReadSensor: public Sensor{
protected:
  HAL* _hal;
  int _pin;
public:
  DigitalReadSensor(HAL* hal, int digital_pin);
  Measurement read();
};

class MPU9250Sensor: public Sensor{
protected:
  float _value;
public:
  MPU9250Sensor(HAL* hal);
  Measurement read();
};




/*************************************************************
 *                    DATA OUTPUT
*************************************************************/
// Interface abstrata para saida de dados
class DataOutput{
public:
  virtual void save(Measurement data) = 0;
};


class PrintOutput: public DataOutput{
public:
  PrintOutput();
  void save(Measurement data);
};

class SDCardOutput: public DataOutput{
public:
  SDCardOutput();
  void save(Measurement data);
};

class DigitalPinOutput: public DataOutput{
protected:
  HAL* _hal;
  int _pin;
public:
  DigitalPinOutput(HAL* hal, int digital_pin);
  void save(Measurement data);
};


/*************************************************************
 *                    SCHEDULER
*************************************************************/
// Realiza medidas e as salva de forma periódica(talvez generalizar essa parte por um objeto MeasurementStrategy ou algo assim)
// Estruturado em formato de linked list
class Scheduler{
private:
  HAL* _hal;
  float _sample_rate;
  Sensor* _sensor;
  DataOutput* _output;
  time_t _last_measurement_time;
  //utils
  Scheduler* get_last_scheduler();
  int is_time_to_run();
  int is_empty();
public:
  Scheduler* _next;
  Scheduler(HAL* hal, Sensor* sensor, DataOutput* output, float sample_rate);
  Scheduler(HAL* hal); // para uso como head da lista (não realiza nenhuma medida)
  void schedule(Sensor* sensor, DataOutput* output, float sample_rate);
  void update();
  void update_all();
};


/*************************************************************
 *                    MEASUREMENT
*************************************************************/
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
  char* sensor_type(); // ToDo: Analisar se o uso de char* é a melhor opção
  char* sensor_name();
  // char* to_string();
  // char* to_csv();
};


/*************************************************************
 *            HARDWARE ABSTRACTION LAYER
*************************************************************/
// Interface para interação com o hardware
class HAL{
public:
  virtual float analog_read(int analog_pin) = 0;
  virtual int digital_read(int digital_pin) = 0;
  virtual int digital_write(int value, int digital_pin)= 0;
  virtual time_t time() = 0;
};

// Implementações
class HAL_FAKE: public HAL{
public:
  float analog_read(int analog_pin);
  int digital_read(int digital_pin);
  int digital_write(int value, int digital_pin);
  time_t time();
};


class HAL_ATMEGA: public HAL{
public:
  HAL_ATMEGA();
  float analog_read(int analog_pin);
  int digital_read(int digital_pin);
  int digital_write(int value, int digital_pin);
  time_t time();
};


class HAL_ESP32: public HAL{
public:
  HAL_ESP32();
  float analog_read(int analog_pin);
  int digital_read(int digital_pin);
  int digital_write(int value, int digital_pin);
  time_t time();
};



#endif // !SENSORUFSC_H
