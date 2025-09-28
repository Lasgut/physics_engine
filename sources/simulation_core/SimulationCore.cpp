#include "SimulationCore.h"
#include "UnmannedAerialVehicle.h"
#include "Settings.h"

SimulationCore::SimulationCore(ResourceHandler* resourceHandler)
    : resourceHandler_(resourceHandler)
{
    auto& entityKinematics = resourceHandler_->getFiles().entityKinematics;

    auto* drone = new UnmannedAerialVehicle(entityKinematics.generalAircraftKinematicsPath);

    entities_[1] = drone;
}


void 
SimulationCore::update()
{
    if (!Settings::getInstance().simulation.isRunning) 
    {
        return;
    }
    
    //TODO: simulate environment forces and moments

    for (auto& [id, entity] : entities_)
    {
        auto isUpdated = entity->updateEntity();
        if (isUpdated)
        {
            emit entityKinematicsUpdated(id, static_cast<Kinematics*>(entity));
            emit controlSystemDataUpdated(id, &static_cast<UnmannedAerialVehicle*>(entity)->getControlSystemData());
        }
    }
}


Entity*
SimulationCore::getEntity(const int id)
{
    auto it = entities_.find(id);
    if (it != entities_.end())
    {
        return it->second;
    }
    return nullptr; // or handle the case where the entity is not found
}
