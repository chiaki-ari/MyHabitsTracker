#ifndef OUTPUT_MANAGER_HPP
#define OUTPUT_MANAGER_HPP

#include "output/OutputInterface.hpp"

class OutputManager {
public:
    OutputManager(OutputInterface& outputInterface);
    void print(const std::string& message, bool  = true);

private:
    OutputInterface& outputInterface_;
};

#endif // OUTPUT_MANAGER_HPP
