#ifndef SIMULATION_CORE_H
#define SIMULATION_CORE_H

#pragma once

#include <map>
#include <QObject>

#include "UnmannedAerialVehicle.h"
#include "Clock.h"
#include "ResourceHandler.h"
#include "Entity.h"

class SimulationCore
    : public QObject
{
    Q_OBJECT

    public:
        SimulationCore(ResourceHandler* resourceHandler);

        void update();

        Entity* getEntity(const int id);

    private:
        std::map<int, Entity*> entities_;
        Clock                  clock_;
        ResourceHandler*       resourceHandler_;

    signals: 
        void entityKinematicsUpdated(int entityId, Kinematics* kinematics);
        void controlSystemDataUpdated(int entityId, ControlSystemData* ctrlSysData);
};

#endif