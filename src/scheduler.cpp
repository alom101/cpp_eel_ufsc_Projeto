#include "sensorUFSC.h"
#include <cstdio>
#include <ctime>


Scheduler::Scheduler(HAL* hal, Sensor* sensor, DataOutput* output, float sample_rate){
  _hal = hal;
  _sensor = sensor;
  _output = output;
  _sample_rate = sample_rate;
  _next_measurement_time = _hal->time();
}

Scheduler::Scheduler(HAL* hal){
  _hal = hal;
  _sensor = 0;
  _output = 0;
  _sample_rate = 1;
  _next_measurement_time = 0;
  _next = nullptr;
}

Scheduler* Scheduler::get_last_scheduler(){
  Scheduler* ret = this;
  while(ret->_next){
    ret = ret->_next;
  }
  return ret;
}

int Scheduler::is_time_to_run(){
  return difftime(_hal->time(), _next_measurement_time) >=0;
}

int Scheduler::is_empty(){
  return _sensor==0 or _output==0 or _sample_rate==0;
}

void Scheduler::schedule(Sensor* sensor, DataOutput* output, float sample_rate){
  Scheduler* last_scheduler = get_last_scheduler();
  _next = new Scheduler(_hal, sensor, output, sample_rate);
}
void Scheduler::update(){
  if(is_time_to_run() and !is_empty()){
    printf("UPDATING!\t");
    _output->save(_sensor->read());
    _next_measurement_time += 1/_sample_rate;
    printf("\nNEXT UPDATE: %s\n\n", std::ctime(&_next_measurement_time));
  }
}

void Scheduler::update_all(){
  Scheduler* scheduler = this;
  while(scheduler){
    scheduler->update();
    scheduler = scheduler->_next;
  }
}


