#include "sensorUFSC.h"


int main (int argc, char *argv[]) {
  // Sensor* sensor = new FakeSensor(10.1);
  HAL* hal = new HAL_DEFAULT();

  Sensor* sensor_1 = new FakeSensor(hal, 1.0);
  char nome_do_sensor_1[SENSOR_NAME_LEN] = "Sensor de testes 1";
  sensor_1->set_sensor_name(nome_do_sensor_1);

  Sensor* sensor_2 = new FakeSensor(hal, 2.0);
  char nome_do_sensor_2[SENSOR_NAME_LEN] = "Sensor de testes 2";
  sensor_2->set_sensor_name(nome_do_sensor_2);

  DataOutput* output = new PrintOutput();

  Scheduler* schedulers = new Scheduler(hal);
  schedulers->schedule(sensor_1, output, 1./2);
  schedulers->schedule(sensor_2, output, 1./4);

  while(1){
    schedulers->update_all();
 }

  return 0;
}
