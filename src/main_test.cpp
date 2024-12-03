#include "sensorUFSC.h"
#include <cstdio>
#include <ctime>


int main (int argc, char *argv[]) {
  Sensor* s = new FakeSensor(10.1);
  char nome_do_sensor[] = "Sensor de testes";
  s->set_sensor_name(nome_do_sensor);


  for(int i=0; i<5; i++){
    Measurement m = s->read();

    // time_t t = m.timestamp(); 
    // printf("%d)Medida %f feita em %s do tipo %s em %s\n", i, m.value(), m.sensor_name(), m.sensor_type(), ctime(&t));
    
    printf("%d) %s", i, m.to_string());
  }
  return 0;
}
