#include "UnmannedAerialVehicle.h"
#include "EventState.h"
#include "Entity.h"
#include <iostream>

UnmannedAerialVehicle::UnmannedAerialVehicle(const std::string &kinematicsFilePath)
    : Entity(kinematicsFilePath)
{
}


Eigen::Vector<double, 6>
UnmannedAerialVehicle::appliedForcesAndMoments()
{
    auto sensorData            = emulateSensorData(kinematics_);
    auto desiredActuatorStates = iterateControlLoop(sensorData);
    auto controlForces         = emulateActuatorDynamics(desiredActuatorStates);

    // static Clock debugClock;
    // if (debugClock.rateLimit(1))
    // {
    //     std::cout << "DEBUG: controlForces: " << controlForces.transpose() << std::endl;
    // }
    // std::cout << "DEBUG: appliedForcesAndMoments - position: " << kinematics_.getPosition().transpose() << " velocity: " << kinematics_.getVelocity().transpose() << std::endl;

    //Aircraft 
    // Eigen::Vector<double,6> controlForces(0,0,0,0,0,0);
    // Eigen::Vector3d         desiredRates(0, 0, 0); // [p_ref, q_ref, r_ref] (roll, pitch, yaw rates)

    // if (EventState::getInstance().keyboard.up)
    //     desiredRates[1] = -0.5; // Pitch down
    // if (EventState::getInstance().keyboard.down)
    //     desiredRates[1] = 0.5;  // Pitch up
    // if (EventState::getInstance().keyboard.left)
    //     desiredRates[0] = -0.5; // Roll left
    // if (EventState::getInstance().keyboard.right)
    //     desiredRates[0] = 0.5;  // Roll right
    // if (EventState::getInstance().keyboard.space)
    //     controlForces[0] = 2.0; // Thrust (optional for now)
    // else
    //     controlForces[0] = velocityController_.control(12, kinematics_.getVelocity()[0]);

    // // if (desiredRates[1] == 0)
    // //     desiredRates[1]= pitchController_.control(0.0, kinematics_.getEulerAngles()[1]);

    // controlForces[3] = rollRateController_.control(desiredRates[0], kinematics_.getAngularVelocity()[0]);
    // controlForces[4] = pitchRateController_.control(desiredRates[1], kinematics_.getAngularVelocity()[1]);

    // underwater
    // double force = 0.3;
    // Eigen::Vector<double,6> controlForces(0,0,0,0,0,0);
    // if (EventState::getInstance().keyboard.up)
    // {
    //     controlForces[0] = force;
    // }
    // if (EventState::getInstance().keyboard.down)
    // {
    //     controlForces[0] = -force;
    // }
    // if (EventState::getInstance().keyboard.left)
    // {
    //     controlForces[5] = -0.2*force;
    // }
    // if (EventState::getInstance().keyboard.right)
    // {
    //     controlForces[5] = 0.2*force;
    // }
    // if (EventState::getInstance().keyboard.space)
    // {
    //     controlForces[2] = force;
    // }
    return controlForces;
}