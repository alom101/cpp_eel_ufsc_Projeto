#include "sensorUFSC.h"



PrintOutput::PrintOutput(){
};

int PrintOutput::save(Measurement data){
  time_t t = data.timestamp(); 
  printf("Medida %f feita em %s do tipo %s em %s\n", data.value(), data.sensor_name(), data.sensor_type(), ctime(&t));
  return 1;
}
