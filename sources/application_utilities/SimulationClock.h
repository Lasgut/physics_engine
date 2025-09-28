#ifndef SIMULATIONCLOCK_H
#define SIMULATIONCLOCK_H

#pragma once
#include <chrono>
#include <thread>
#include <atomic>

#include "Settings.h"


class SimulationClock
{
    public:
        static SimulationClock& getInstance()
        {
            static SimulationClock instance;
            return instance;
        };

        double getTime();

    private:
        SimulationClock();
        ~SimulationClock()                                 = default;
        SimulationClock(const SimulationClock&)            = delete;
        SimulationClock& operator=(const SimulationClock&) = delete;
        SimulationClock(SimulationClock&&)                 = delete;
        SimulationClock& operator=(SimulationClock&&)      = delete;

        void startSimulationClock();

        std::atomic<double> simulationTime_; // simulation time in sec since start time
        std::chrono::steady_clock::time_point      prevSimTimeUpdate_;
        std::thread                                simulationClockThread_;

};

#endif