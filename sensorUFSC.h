#ifndef SENSORUFSC_H
#define SENSORUFSC_H

class Sensor;
class DataOutput;
class Measurement;
// class MeasurementStrategy;


// Interface abstrata para sensores
class Sensor{
private:

protected:

public:
  // CORE
  Measurement read();

  // METADATA
  char* sensor_type();
  char* sensor_name();
  
};


// Interface abstrata para saida de dados
class DataOutput{
private:

protected:

public:
  int save(Measurement data);
};



// Realiza medidas e as salva de forma peroódica(talvez generalizar essa parte por um objeto MeasurementStrategy ou algo assim)
class Scheduler{
private:

protected:

public:
  Scheduler(Sensor* sensor, DataOutput* output, float sample_rate);
};


// Encapsula a medida, para facilitar alterações. Também disponibiliza alguns metadados.
class Measurement{
private:

protected:

public:
  float value();
  char* sensor_type();
  char* sensor_name();
};


#endif // !SENSORUFSC_H
