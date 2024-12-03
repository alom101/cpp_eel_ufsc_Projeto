#include "sensorUFSC.h"
#include <cstdio>
#include <ctime>


int main (int argc, char *argv[]) {
  // Sensor* sensor = new FakeSensor(10.1);
  HAL* hal = new HAL_DEFAULT();
  Sensor* sensor = new AnalogReadSensor(hal, 6);
  char nome_do_sensor[] = "Sensor de testes";
  sensor->set_sensor_name(nome_do_sensor);

  DataOutput* output = new PrintOutput();


  for(int i=0; i<5; i++){
    Measurement m = sensor->read();
    output->save(m);
  }
  return 0;
}
