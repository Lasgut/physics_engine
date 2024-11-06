#include "Clock.h"
#include <chrono>

Clock::Clock()
{
}

Clock::~Clock()
{
}

void Clock::setPreviousTime()
{
    previousTime_ = std::chrono::steady_clock::now();
}

float 
Clock::getDeltaTime() const
{
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> deltaTime = currentTime - previousTime_;
    return deltaTime.count();
}
