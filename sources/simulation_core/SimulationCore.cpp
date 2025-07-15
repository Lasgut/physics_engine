#include "SimulationCore.h"

SimulationCore::SimulationCore(ResourceHandler* resourceHandler)
    : resourceHandler_(resourceHandler)
{
    auto& entityKinematics = resourceHandler_->getFiles().entityKinematics;

    auto* drone = new Entity(entityKinematics.generalAircraftKinematicsPath);

    entities_[1] = drone;
}


void 
SimulationCore::update()
{
    for (auto& [id, entity] : entities_)
    {
        auto isUpdated = entity->update();
        if (isUpdated)
        {
            emit entityKinematicsUpdated(
                id, 
                entity->getPosition(), 
                entity->getOrientation()
            );
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