#ifndef CLOCK_H
#define CLOCK_H

#pragma once
#include <chrono>

class Clock
{
public:
    Clock();
    ~Clock();

    void  setPreviousTime();
    float getDeltaTime()    const;

private:
    std::chrono::steady_clock::time_point previousTime_;
};

#endif