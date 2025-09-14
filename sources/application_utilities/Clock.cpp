#include "Clock.h"
#include <chrono>
#include <iostream>

Clock::Clock()
{
    previousTime_ = std::chrono::steady_clock::now();
}

Clock::Clock(const double frequency)
    : frequency_(frequency)
{
    Clock();
}


float 
Clock::getDeltaTime()
{
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> deltaTime = currentTime - previousTime_;
    return deltaTime.count();
}


bool 
Clock::rateLimit()
{
    auto desiredDeltaTime = 1.0f / frequency_;
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - previousTime_;
    bool pastDeltaTime = elapsedTime.count() >= desiredDeltaTime;
    if (pastDeltaTime)
    {
        previousTime_ = currentTime;
    }
    return pastDeltaTime;
}


bool 
Clock::rateLimit(double& deltaTime)
{
    auto desiredDeltaTime = 1.0f / frequency_;
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - previousTime_;
    bool pastDeltaTime = elapsedTime.count() >= desiredDeltaTime;
    if (pastDeltaTime)
    {
        previousTime_ = currentTime;
    }
    deltaTime = elapsedTime.count();
    return pastDeltaTime;
}


bool 
Clock::rateLimit(const int frequency)
{
    auto desiredDeltaTime = 1.0f / frequency;
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - previousTime_;
    bool pastDeltaTime = elapsedTime.count() >= desiredDeltaTime;
    if (pastDeltaTime)
    {
        previousTime_ = currentTime;
    }
    return pastDeltaTime;
}


void 
Clock::setPreviousTime()
{
    previousTime_ = std::chrono::steady_clock::now();
}


void
Clock::setFrequency(const double frequency)
{
    frequency_ = frequency;
}


float
Clock::now()
{
    return std::chrono::steady_clock::now().time_since_epoch().count();
}
