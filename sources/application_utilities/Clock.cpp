#include "Clock.h"
#include <chrono>
#include <iostream>
#include <pthread.h>


Clock::Clock()
{
    previousTime_ = simClock_.getTime();
}


Clock::Clock(std::string name)
    : name_(name)
{
    Clock();
}


Clock::Clock(const double frequency)
    : frequency_(frequency)
{
    Clock();
}


Clock::Clock(const double frequency, std::string name)
    : name_(name)
    , frequency_(frequency)
{
    Clock();
}


double 
Clock::getDeltaTime()
{
    return elapsedTime_;
}


bool 
Clock::rateLimit()
{
    auto desiredDeltaTime = 1.0f / frequency_;
    auto currentTime = simClock_.getTime();
    elapsedTime_ = currentTime - previousTime_;
    bool pastDeltaTime = elapsedTime_ >= desiredDeltaTime;
    if (pastDeltaTime)
    {
        previousTime_ = currentTime;
    }
    fallingBehindCheck(desiredDeltaTime, elapsedTime_);
    return pastDeltaTime;
}


bool 
Clock::rateLimit(const int frequency)
{
    frequency_ = frequency;
    bool pastDeltaTime = rateLimit();
    return pastDeltaTime;
}


void 
Clock::setPreviousTime()
{
    previousTime_ = simClock_.getTime();
}


void
Clock::setFrequency(const double frequency)
{
    frequency_ = frequency;
}


double
Clock::now()
{
    return simClock_.getTime();
}


void 
Clock::fallingBehindCheck(double desiredDeltaTime, double elapsedTime)
{
    if (elapsedTime > desiredDeltaTime * 1.05)
    {
        std::cout << "Warning: " << name_ << " clock is falling behind with " << elapsedTime-desiredDeltaTime << " seconds! Desired delta time is " << desiredDeltaTime << ", and elapsed time is " << elapsedTime << std::endl;
    }
}
