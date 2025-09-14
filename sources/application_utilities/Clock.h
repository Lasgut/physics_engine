#ifndef CLOCK_H
#define CLOCK_H

#pragma once
#include <chrono>

class Clock
{
public:
    Clock();
    Clock(const double frequency);

    float getDeltaTime();
    bool  rateLimit();
    bool  rateLimit(double& deltaTime);
    bool  rateLimit(const int frequency);
    void  setPreviousTime();
    void  setFrequency(const double frequency);
    float now();

private:
    std::chrono::steady_clock::time_point previousTime_;
    std::chrono::duration<float>          elapsedTime_;
    double                                frequency_{1.0}; // default frequency
};

#endif