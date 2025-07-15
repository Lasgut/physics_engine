#ifndef ENTITY_H
#define ENTITY_H

#pragma once
#include "shapes/StlMesh.h"
#include "entity_utilities/Kinematics.h"
#include "entity_utilities/PidController.h"
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

    private:
        void init(const std::string& kinematicsFilePath);

        Eigen::Vector<double,6> computeControlForces();

        Kinematics    kinematics_;
        PidController pitchController_{1,0,0,7};
        PidController pitchRateController_{1,0,0,20};
        PidController rollRateController_{1,0,0,20};
        PidController velocityController_{1,0,0,20};
};

#endif