#include "Kinematics.h"
#include "KinematicsData.h"
#include "KinematicsLib.h"
#include "Settings.h"
#include <Eigen/Dense>
#include <glm/glm.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <optional>
#include <glm/gtc/quaternion.hpp>


void 
Kinematics::loadKinematicsData(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open JSON file: " + filePath);
    }
    nlohmann::json jsonData;
    file >> jsonData;

    // Extract data from json
    try
    {
        data_.type    = jsonData["type"];

        auto& general = data_.general;
        general.mass = jsonData["mass"];
        auto r_bg    = jsonData.at("centerOfGravity");
        general.r_bg = Eigen::Vector<double,3>(r_bg[0], r_bg[1], r_bg[2]);

        auto inertia = jsonData.at("inertia");
        general.I_xx = inertia["I_xx"];
        general.I_yy = inertia["I_yy"];
        general.I_zz = inertia["I_zz"];
        general.I_xz = inertia.contains("I_xz") ? inertia["I_xz"].get<double>() : 0.0;

        if (data_.type == "underwater" || data_.type == "ROV")
        {
            auto& uw = data_.underwater;

            uw.buoyancy = jsonData["buoyancy"];
            auto r_bb   = jsonData.at("centerOfBuoyancy");
            uw.r_bb     = Eigen::Vector<double,3>(r_bb[0], r_bb[1], r_bb[2]);

            auto addedMass = jsonData.at("added_mass");
            uw.Xudot    = addedMass["Xudot"];
            uw.Yvdot    = addedMass["Yvdot"];
            uw.Zwdot    = addedMass["Zwdot"];
            uw.Kpdot    = addedMass["Kpdot"];
            uw.Mqdot    = addedMass["Mqdot"];
            uw.Nrdot    = addedMass["Nrdot"];

            auto linearDamping = jsonData.at("linear_damping");
            uw.Xu       = linearDamping["Xu"];
            uw.Yv       = linearDamping["Yv"];
            uw.Zw       = linearDamping["Zw"];
            uw.Kp       = linearDamping["Kp"];
            uw.Mq       = linearDamping["Mq"];
            uw.Nr       = linearDamping["Nr"];
            
            auto quadraticDamping = jsonData.at("quadratic_damping");
            uw.Xuu      = quadraticDamping["Xuu"];
            uw.Yvv      = quadraticDamping["Yvv"];
            uw.Zww      = quadraticDamping["Zww"];
            uw.Kpp      = quadraticDamping["Kpp"];
            uw.Mqq      = quadraticDamping["Mqq"];
            uw.Nrr      = quadraticDamping["Nrr"];
        }
        if (data_.type == "aircraft" || data_.type == "UAV")
        {
            auto& ac = data_.aircraft;

            auto aero = jsonData.at("aero");
            ac.S         = aero["wingArea"];
            ac.b         = aero["span"];
            ac.c         = aero["chord"];
        
            ac.CL_0      = aero["CL_0"];
            ac.CL_alpha  = aero["CL_alpha"];
            ac.CL_q      = aero["CL_q"];

            ac.CY_0      = aero["CY_0"];
            ac.CY_beta   = aero["CY_beta"];
            ac.CY_p      = aero["CY_p"];
            ac.CY_r      = aero["CY_r"];
            
            ac.CD_0      = aero["CD_0"];
            ac.CD_alpha  = aero["CD_alpha"];
            ac.CD_q      = aero["CD_q"];

            ac.Cm_0      = aero["Cm_0"];
            ac.Cm_alpha  = aero["Cm_alpha"];
            ac.Cm_q      = aero["Cm_q"];

            ac.Cl_0      = aero["Cl_0"];
            ac.Cl_beta   = aero["Cl_beta"];
            ac.Cl_p      = aero["Cl_p"];
            ac.Cl_r      = aero["Cl_r"];

            ac.Cn_0      = aero["Cn_0"];
            ac.Cn_beta   = aero["Cn_beta"];
            ac.Cn_p      = aero["Cn_p"];
            ac.Cn_r      = aero["Cn_r"];
        }
    }
    catch (const nlohmann::json::exception& e) 
    {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        throw;
    }
}


void 
Kinematics::eulerIntegration(const double deltaTime)
{
    data_.nu  += data_.nuDot  * deltaTime;
    data_.eta += data_.etaDot * deltaTime;
}


double 
Kinematics::deg2rad(double degrees) const
{
    return degrees * M_PI / 180.0;
}


double 
Kinematics::rad2deg(double radians) const
{
    return radians * 180.0 / M_PI;
}


void 
Kinematics::setPosition(const Eigen::Vector3<double>& pos) 
{
    data_.setPosition(pos);
}


void 
Kinematics::setVelocity(const Eigen::Vector3<double>& vel) 
{
    data_.setVelocity(vel);
}


void 
Kinematics::setOrientation(const Eigen::Quaterniond& orient) 
{
    data_.setOrientationQuat(orient);
}


void 
Kinematics::setMass(double mass) 
{
    data_.general.mass = mass;
}


void 
Kinematics::setFrequency(double frequency)
{
    frequency_ = frequency;
}


Eigen::Vector3<double>
Kinematics::getPosition() const 
{
    return data_.getPosition();
}


Eigen::Vector3<double>
Kinematics::getVelocity() const 
{
    return data_.getVelocity();
}


Eigen::Quaterniond
Kinematics::getOrientation() const 
{
    return Eigen::Quaterniond(data_.getOrientationQuat());
}


Eigen::Vector3d 
Kinematics::getEulerAngles() const
{
    return data_.getOrientationEuler();
}


Eigen::Vector3d
Kinematics::getAngularVelocity() const
{
    return data_.getAngularVelocity();
}


double 
Kinematics::getMass() const 
{
    return data_.general.mass;
}


glm::vec3
Kinematics::getPositionAsGlm() const
{
    glm::vec3 pos;
    pos.x = data_.getPosition().x();
    pos.y = data_.getPosition().y();
    pos.z = data_.getPosition().z();
    return pos;
}


glm::quat
Kinematics::getOrientationAsGlm() const
{
    glm::quat ori;
    ori.x = data_.getOrientationQuat().x();
    ori.y = data_.getOrientationQuat().y();
    ori.z = data_.getOrientationQuat().z();
    ori.w = data_.getOrientationQuat().w();
    return ori;
}


void
Kinematics::update(Eigen::Vector<double,6> tau)
{
    if (!settings_.simulation.isRunning) 
    {
        clock_.setPreviousTime();
        return;
    }
    if (!clock_.rateLimit(frequency_)) 
    {
        return;
    }
    //auto deltaTime = clock_.getDeltaTime();
    auto deltaTime = 1.0f / frequency_;

    data_.tau = tau;
    if (data_.type == "aircraft" || data_.type == "UAV")
    {
        Lib::Kinematics::Aircraft::computeAircraftDynamics(data_);
    }
    if (data_.type == "ROV")
    {
        Lib::Kinematics::Underwater::computeUnderwaterVehicleDynamics(data_);
    }

    eulerIntegration(deltaTime);

    Eigen::Vector3d eulerAngles = data_.getOrientationEuler();
    if (clockDebug_.rateLimit(2))
    {
        clockDebug_.setPreviousTime();
        std::cout << "Control Forces:  " << data_.tau.transpose() << std::endl;
        std::cout << "Position:        " << data_.getPosition().transpose() << std::endl;
        std::cout << "Orientation:     " << eulerAngles.transpose() << std::endl;
        std::cout << "velocity:        " << data_.getVelocity().transpose() << std::endl;
        std::cout << "angularVelocity: " << data_.getAngularVelocity().transpose() << std::endl;
        std::cout << "eta:             " << data_.eta.transpose() << std::endl;
        std::cout << "nu:              " << data_.nu.transpose() << std::endl;
        std::cout << "nuDot:           " << data_.nuDot.transpose() << std::endl;
    }
}
