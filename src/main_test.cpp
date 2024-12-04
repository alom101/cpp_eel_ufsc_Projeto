#include "sensorUFSC.h"


int main (int argc, char *argv[]) {
  HAL* hal = new HAL_DEFAULT();
  DataOutput* output = new PrintOutput();


  Sensor* sensor_1 = new FakeSensor(hal, 1.0);
  sensor_1->set_sensor_name("Sensor de testes 1");

  Sensor* sensor_2 = new FakeSensor(hal, 2.0);
  sensor_2->set_sensor_name("Sensor de testes 2");


  Scheduler* schedulers = new Scheduler(hal);
  schedulers->schedule(sensor_1, output, 1./2);
  schedulers->schedule(sensor_2, output, 1./4);

  while(1){
    schedulers->update_all();
 }

  return 0;
}
