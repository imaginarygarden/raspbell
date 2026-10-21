#ifndef DEVICE_H
#define DEVICE_H

#include <string>

struct Device {
    int id = 0;
    std::string name;
    std::string password;
};

#endif