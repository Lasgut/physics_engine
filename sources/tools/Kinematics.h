#ifndef KINEMATICS_H
#define KINEMATICS_H

#pragma once
#include "KinematicsData.h"
#include "Clock.h"
#include "Settings.h"
#include <Eigen/Dense>
#include <glm/glm.hpp>
#include <optional>

class Kinematics
{
public:
    Kinematics() = default;

    void loadKinematicsData(const std::string& filePath);

    void setPosition    (const Eigen::Vector3<double>& pos);
    void setVelocity    (const Eigen::Vector3<double>& vel);
    void setOrientation (const Eigen::Quaterniond&     orient);
    void setMass        (double mass);
    void setFrequency   (double frequency);

    Eigen::Vector<double,3>  getPosition()    const;
    Eigen::Vector<double,3>  getVelocity()    const;
    Eigen::Quaterniond       getOrientation() const;
    double                   getMass()        const;

    glm::vec3 getPositionAsGlm()    const;
    glm::quat getOrientationAsGlm() const;

    void update(Eigen::Vector<double,6> controlForces);

private:
    void updateSystemMatrices();
    void updateMassMatrix();
    void updateCoriolisMatrix();
    void updateDampingMatrix();

    void underwaterDynamics(const double deltaTime);
    void aircraftDynamics(const double deltaTime);

    void eulerIntegration(const double deltaTime);

    double deg2rad(double degrees) const;
    double rad2deg(double radians) const;

    Eigen::Matrix<double,3,3> skew(const Eigen::Vector<double,3>& v);
    Eigen::Matrix<double,3,3> Rzyx(double phi, double theta, double psi); 
    Eigen::Matrix<double,3,3> Tzyx(double phi, double theta); 
    Eigen::Matrix<double,3,3> Rquat(const Eigen::Quaterniond& q);
    Eigen::Matrix<double,4,3> Tquat(const Eigen::Quaterniond& q);

    double frequency_{400};

    KinematicsData data_; 
    Clock          clock_;
    Clock          clockDebug_;
    Settings&      settings_ = Settings::getInstance();
};

#endif