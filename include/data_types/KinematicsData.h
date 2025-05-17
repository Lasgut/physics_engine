#ifndef KINEMATICSDATA_H
#define KINEMATICSDATA_H

#pragma once
#include <Eigen/Dense>

struct KinematicsData 
{
    // eta = [pos, Theta]
    //       p = [x, y, z]
    //   Theta = [phi, theta, psi]
    //
    // nu  = [vel, omega]
    //     vel = [u, v, w]
    //   omega = [p, q, r]

    Eigen::Vector<double,6> nu      {0,0,0,0,0,0};
    Eigen::Vector<double,6> nuDot   {0,0,0,0,0,0};
    Eigen::Vector<double,7> eta     {0,0,0,1,0,0,0};
    Eigen::Vector<double,7> etaDot  {0,0,0,1,0,0,0};

    Eigen::Vector3d    getPosition()            const { return eta.head<3>();   }
    Eigen::Quaterniond getOrientationQuat()     const { return {eta(3),eta(4),eta(5),eta(6)};   }
    Eigen::Vector3d    getVelocity()            const { return nu.head<3>();    }
    Eigen::Vector3d    getAngularVelocity()     const { return nu.tail<3>();    }
    Eigen::Vector3d    getAcceleration()        const { return nuDot.head<3>(); }
    Eigen::Vector3d    getAngularAcceleration() const { return nuDot.tail<3>(); }

    void setPosition            (const Eigen::Vector3d&    pos)    { eta.head<3>()   = pos;    }
    void setOrientationQuat     (const Eigen::Quaterniond& ori)    { eta(3) = ori.w(); eta.tail<3>() = ori.vec(); }
    void setVelocity            (const Eigen::Vector3d&    vel)    { nu.head<3>()    = vel;    }
    void setAngularVelocity     (const Eigen::Vector3d&    angVel) { nu.tail<3>()    = angVel; }
    void setAcceleration        (const Eigen::Vector3d&    acc)    { nuDot.head<3>() = acc;    }
    void setAngularAcceleration (const Eigen::Vector3d&    angAcc) { nuDot.tail<3>() = angAcc; }
    
    double mass    {0}; // kg
    double buoyancy{0}; // N  
    double gravity {0}; // m/s^2

    Eigen::Vector<double,3> r_bg{0,0,0}; // Center of gravity
    Eigen::Vector<double,3> r_bb{0,0,0}; // Center of buoyancy

    // Inertia
    double I_xx{0};
    double I_yy{0};
    double I_zz{0};

    // Added Mass
    double Xu{0};
    double Yv{0};
    double Zw{0};
    double Kp{0};
    double Mq{0};
    double Nr{0};

    // Linear Damping
    double Xudot{0};
    double Yvdot{0};
    double Zwdot{0};
    double Kpdot{0};
    double Mqdot{0};
    double Nrdot{0};

    // Quadratic Damping
    double Xuu{0};
    double Yvv{0};
    double Zww{0};
    double Kpp{0};
    double Mqq{0};
    double Nrr{0};

    // System Matrices
    Eigen::Matrix<double,6,6> M_RB; 
    Eigen::Matrix<double,6,6> M_A;
    Eigen::Matrix<double,6,6> M;
    Eigen::Matrix<double,6,6> C;
    Eigen::Matrix<double,6,6> D_lin;
    Eigen::Matrix<double,6,6> D_quad;
    Eigen::Matrix<double,6,6> D;
};

#endif