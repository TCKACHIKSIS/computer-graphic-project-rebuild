#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include <iostream>
#include <vector>
#include "canalofsignal/canalofsignal.h"

typedef struct dataStructure{
  int number_of_channels = 0;
  int number_of_samples = 0;
  double sampling_frequency = 0;
  double recording_duration = 0;
  double period_of_tick = 0;
  std::string signal_start_date;
  std::string signal_start_time;
  std::vector<std::string> channels_names;
  std::vector<CanalOfSignal> signals_channels;

}dataStructure;

#endif // DATASTRUCTURE_H
