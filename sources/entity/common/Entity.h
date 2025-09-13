#ifndef ENTITY_H
#define ENTITY_H

#pragma once
#include "entity_utilities/Kinematics.h"
#include "Clock.h"

class Entity
{
    public:
        Entity(const std::string& kinematicsFilePath);

        bool update();
        
        Eigen::Vector3<double> getPosition()        const;
        Eigen::Quaterniond     getOrientation()     const;
        Eigen::Vector3<double> getEulerAngles()     const;

        glm::vec3 getPositionAsGlm()    const;
        glm::quat getOrientationAsGlm() const;

    protected:
        Kinematics kinematics_;

    private:
        void init(const std::string& kinematicsFilePath);

        virtual Eigen::Vector<double,6> appliedForcesAndMoments() {return {};};
};

#endif