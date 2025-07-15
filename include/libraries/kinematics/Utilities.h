#pragma once

#include "KinematicsData.h"
#include <Eigen/Dense>
#include <iostream>

namespace Lib::Kinematics::Utils
{
    inline Eigen::Matrix<double,3,3>
    skew(const Eigen::Vector<double,3>& v) 
    {
        Eigen::Matrix<double,3,3> skewMat;
        skewMat <<    0, -v(2),  v(1),
                v(2),     0, -v(0),
                -v(1),  v(0),     0;
        return skewMat;
    }


    inline Eigen::Matrix<double,3,3>
    Rzyx(double phi, double theta, double psi) 
    {
        // Compute trigonometric functions
        double cphi = cos(phi);
        double sphi = sin(phi);
        double cth  = cos(theta);
        double sth  = sin(theta);
        double cpsi = cos(psi);
        double spsi = sin(psi);

        // Construct rotation matrix
        Eigen::Matrix<double,3,3> R;
        R << cpsi*cth, (-spsi*cphi) + (cpsi*sth*sphi), ( spsi*sphi) + (cpsi*cphi*sth),
            spsi*cth, ( cpsi*cphi) + (sphi*sth*spsi), (-cpsi*sphi) + (sth*spsi*cphi),
            -sth    , ( cth *sphi)                  , ( cth *cphi);

        return R;
    }


    inline Eigen::Matrix<double,3,3>
    Tzyx(double phi, double theta) 
    {
        // Compute trigonometric functions
        double cphi = cos(phi);
        double sphi = sin(phi);
        double cth = cos(theta);
        double sth = sin(theta);

        // Handle singularity when cth = 0 (i.e., theta = +-90 degrees)
        if (cth == 0) {
            throw std::runtime_error("Tzyx is singular for theta = +-90 degrees");
        }

        // Construct transformation matrix
        Eigen::Matrix<double,3,3> T;
        T << 1, (sphi*sth)/cth, (cphi*sth)/cth,
            0,  cphi         , -sphi,
            0,  sphi/cth     ,  cphi/cth;

        return T;
    }


    inline Eigen::Matrix<double, 3, 3> 
    Rquat(const Eigen::Quaterniond &q)
    {
        constexpr double tol = 1e-2;
        if (std::abs(q.norm() - 1.0) > tol) 
        {
            std::cout << "Quaternion: " << q.coeffs().transpose() << std::endl;
            std::cout << "Quaternion norm: " << q.norm() << std::endl;
            std::cout << "Quaternion norm diff: " << std::abs(q.norm() - 1.0) << std::endl;
            throw std::runtime_error("norm(q) must be equal to 1");
        }

        double eta = q.w();
        Eigen::Vector<double,3> eps = q.vec();

        Eigen::Matrix<double,3,3> S = skew(eps);
        Eigen::Matrix<double,3,3> R = Eigen::Matrix3d::Identity() + (2*eta*S) + (2*S*S);
        return R;
    }


    inline Eigen::Matrix<double, 4, 3> 
    Tquat(const Eigen::Quaterniond &q)
    {
        double eta  = q.w();
        double eps1 = q.x();
        double eps2 = q.y();
        double eps3 = q.z();
    
        Eigen::Matrix<double, 4, 3> T;
        T << -eps1, -eps2, -eps3,
              eta,  -eps3,  eps2,
              eps3,  eta,  -eps1,
             -eps2,  eps1,  eta;
    
        return 0.5 * T;
    }


    inline Eigen::Vector3d quat2euler(const Eigen::Quaterniond& q)
    {
        if (std::abs(q.norm() - 1.0) > 1e-2) 
        {
            std::cout << "Quaternion: " << q.coeffs().transpose() << std::endl;
            std::cout << "Quaternion norm: " << q.norm() << std::endl;
            throw std::runtime_error("norm(q) must be equal to 1");
        }
        auto   R     = q.toRotationMatrix();
        double yaw   = std::atan2(R(1,0), R(0,0));
        double pitch = std::asin(-R(2,0));
        double roll  = std::atan2(R(2,1), R(2,2));
        return Eigen::Vector3d(roll, pitch, yaw); // roll, pitch, yaw
    }


    inline double 
    deg2rad(const double degrees)
    {
        return degrees * M_PI / 180.0;
    }


    inline double 
    rad2deg(const double radians)
    {
        return radians * 180.0 / M_PI;
    }
}