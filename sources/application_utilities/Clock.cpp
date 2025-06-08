#include "Clock.h"
#include <chrono>

Clock::Clock()
{
    previousTime_ = std::chrono::steady_clock::now();
}


float 
Clock::getDeltaTime()
{
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> deltaTime = currentTime - previousTime_;
    previousTime_ = currentTime;
    return deltaTime.count();
}


bool 
Clock::rateLimit(const float frequency)
{
    auto desiredDeltaTime = 1.0f / frequency;
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - previousTime_;
    return elapsedTime.count() >= desiredDeltaTime;
}


void 
Clock::setPreviousTime()
{
    previousTime_ = std::chrono::steady_clock::now();
}
