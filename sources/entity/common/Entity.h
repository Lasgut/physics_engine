#ifndef ENTITY_H
#define ENTITY_H

#pragma once
#include "entity_utilities/Kinematics.h"
#include "Clock.h"
#include "EntityStates.h"

class Entity
    : public Kinematics
{
    public:
        Entity(const std::string& kinematicsFilePath);

        bool updateEntity();

    protected:
        EntityStates trueEntityStates_;

    private:
        void init(const std::string& kinematicsFilePath);
        void updateTrueEntityStates();

        virtual Eigen::Vector<double,6> appliedForcesAndMoments() {return {};};
};

#endif