#ifndef CLOCK_H
#define CLOCK_H

#pragma once
#include <chrono>
#include <thread>
#include <atomic>

#include "Settings.h"
#include "SimulationClock.h"

class Clock
{
public:
    Clock();
    Clock(std::string name);
    Clock(const double frequency);
    Clock(const double frequency, std::string name);

    double getDeltaTime();
    bool   rateLimit();
    bool   rateLimit(const int frequency);
    void   setPreviousTime();
    void   setFrequency(const double frequency);
    double now();

private:
    void fallingBehindCheck(double desiredDeltaTime, double elapsedTime);

    std::string name_;
    double      previousTime_;
    double      elapsedTime_;
    double      frequency_{1.0}; // default frequency

    SimulationClock& simClock_ = SimulationClock::getInstance();
};

#endif