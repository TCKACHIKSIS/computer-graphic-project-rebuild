#ifndef CANALOFSIGNAL_H
#define CANALOFSIGNAL_H
#include <vector>
#include <string>

class CanalOfSignal
{
public:
    std::vector<double> values_of_signal;
    std::string name_of_channel;
    CanalOfSignal(std::string name_of_channels);
};

#endif // CANALOFSIGNAL_H