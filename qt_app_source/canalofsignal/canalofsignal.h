#ifndef CANALOFSIGNAL_H
#define CANALOFSIGNAL_H
#include <vector>
#include <string>

class CanalOfSignal
{
public:
    std::vector<double> values_of_signal;
    std::string name_of_channel;
    std::string source_of_channel;
    CanalOfSignal(std::string name, std::string source);
    CanalOfSignal();

    int number_of_samples = 0;
    double sampling_frequency = 0;
    double recording_duration = 0;
    double period_of_tick = 0;
};

#endif // CANALOFSIGNAL_H
