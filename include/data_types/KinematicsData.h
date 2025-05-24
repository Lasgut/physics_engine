#ifndef KINEMATICSDATA_H
#define KINEMATICSDATA_H

#pragma once
#include <Eigen/Dense>

struct KinematicsData 
{
    std::string type;
    // eta = [pos, Theta]
    //       p = [x, y, z]
    //   Theta = [w, x, y, z] (quaternion representation)
    //
    // nu  = [vel, omega]
    //     vel = [u, v, w]
    //   omega = [p, q, r]

    Eigen::Vector<double,6> nu      {0,0,0,0,0,0};
    Eigen::Vector<double,6> nuDot   {0,0,0,0,0,0};
    Eigen::Vector<double,7> eta     {0,0,0,1,0,0,0};
    Eigen::Vector<double,7> etaDot  {0,0,0,1,0,0,0};

    Eigen::Vector<double,6> tau{0,0,0,0,0,0}; // Added forces and moments (control forces, noise, etc.)

    Eigen::Vector3d    getPosition()            const { return eta.head<3>();   }
    Eigen::Quaterniond getOrientationQuat()     const { return {eta(3),eta(4),eta(5),eta(6)}; }
    Eigen::Vector3d    getOrientationEuler()    const { return getOrientationQuat().toRotationMatrix().eulerAngles(0, 1, 2); }
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
    
    struct GeneralKinematicsData
    {
    // Mass properties
    double mass{0}; // kg
    double I_xx{0};
    double I_yy{0};
    double I_zz{0};
    double I_xz{0};

    Eigen::Vector<double,3> r_bg{0,0,0}; // Center of gravity

    Eigen::Matrix<double,6,6> M; // Mass matrix
    } general;

    struct UnderwaterKinematicsData
    {
        double buoyancy{0}; // N  

        Eigen::Vector<double,3> r_bb{0,0,0}; // Center of buoyancy

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
        Eigen::Matrix<double,6,6> M_RB;   // rigid body mass matrix
        Eigen::Matrix<double,6,6> M_A;    // added mass matrix
        Eigen::Matrix<double,6,6> C;      // Coriolis and centripetal matrix
        Eigen::Matrix<double,6,6> D_lin;  // Linear damping matrix
        Eigen::Matrix<double,6,6> D_quad; // Quadratic damping matrix
        Eigen::Matrix<double,6,6> D;      // Total damping matrix
    } underwater;

    struct AircraftKinematicsData
    {
        // Aerodynamic coefficients
        // Symmetric aircraft: CY_0 = Cl_0 = Cn_0 = 0

        double S{0};        // Wing surface area, m^2
        double b{0};        // Wingspan, m
        double c{0};        // Mean aerodynamic chord, m
        
        double CL_0{0};     // Lift coefficient at zero angle of attack
        double CL_alpha{0}; // Lift coefficient slope
        double CL_q{0};     // Lift coefficient due to pitch rate
        
        double CY_0{0};     // Side force coefficient at zero sideslip
        double CY_beta{0};  // Side force coefficient slope with respect to sideslip angle
        double CY_p{0};     // Side force coefficient due to roll rate
        double CY_r{0};     // Side force coefficient due to yaw rate
        
        double CD_0{0};     // Drag coefficient at zero angle of attack
        double CD_alpha{0}; // Drag coefficient slope with respect to angle of attack
        double CD_q{0};     // Drag coefficient due to pitch rate
        
        double Cm_0{0};     // Pitching moment coefficient at zero angle of attack
        double Cm_alpha{0}; // Pitching moment coefficient slope with respect to angle of attack
        double Cm_q{0};     // Pitching moment coefficient due to pitch rate
        
        double Cl_0{0};     // Rolling moment coefficient at zero sideslip
        double Cl_beta{0};  // Rolling moment coefficient slope with respect to sideslip angle
        double Cl_p{0};     // Rolling moment coefficient due to roll rate
        double Cl_r{0};     // Rolling moment coefficient due to yaw rate
        
        double Cn_0{0};     // Yawing moment coefficient at zero sideslip
        double Cn_beta{0};  // Yawing moment coefficient slope with respect to sideslip angle
        double Cn_p{0};     // Yawing moment coefficient due to roll rate
        double Cn_r{0};     // Yawing moment coefficient due to yaw rate
    
    } aircraft;
};

#endif