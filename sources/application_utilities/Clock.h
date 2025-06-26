#ifndef CLOCK_H
#define CLOCK_H

#pragma once
#include <chrono>

class Clock
{
public:
    Clock();

    float getDeltaTime();
    bool  rateLimit(const float frequency);
    void  setPreviousTime();
    float now();

private:
    std::chrono::steady_clock::time_point previousTime_;
};

#endif