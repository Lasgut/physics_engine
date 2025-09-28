#include "SimulationClock.h"


SimulationClock::SimulationClock()
{
    startSimulationClock();
}


double 
SimulationClock::getTime()
{
    return simulationTime_.load();
}


void 
SimulationClock::startSimulationClock()
{
    simulationClockThread_ = std::thread([this]()
    {
        pthread_setname_np(pthread_self(), "SimulationClock");
        while (true) 
        {
            auto now = std::chrono::steady_clock::now();
            std::chrono::duration<double> delta = now - prevSimTimeUpdate_;
            prevSimTimeUpdate_ = now;
            if (Settings::getInstance().simulation.isRunning)
            {
                simulationTime_.fetch_add(delta.count());
            }
        }
    });
}
