#pragma once

#include "KinematicsData.h"
#include "Utilities.h"
#include <Eigen/Dense>

namespace Lib::Kinematics::Underwater
{
    void 
    computeMassMatrix(KinematicsData& data)
    {
        auto& m     = data.general.mass;
        auto& r_bg  = data.general.r_bg;
        auto& M     = data.general.M;
        auto& I_xx  = data.general.I_xx;
        auto& I_yy  = data.general.I_yy;
        auto& I_zz  = data.general.I_zz;
        auto& I_xz  = data.general.I_xz;
        auto& M_RB  = data.underwater.M_RB;
        auto& M_A   = data.underwater.M_A;
        auto& Xudot = data.underwater.Xudot;
        auto& Yvdot = data.underwater.Yvdot;
        auto& Zwdot = data.underwater.Zwdot;
        auto& Kpdot = data.underwater.Kpdot;
        auto& Mqdot = data.underwater.Mqdot;
        auto& Nrdot = data.underwater.Nrdot;

        Eigen::Matrix3d I = Eigen::Vector<double,3>(I_xx, I_yy, I_zz).asDiagonal();
        I(0,2) = I_xz;

        M_RB.block<3,3>(0,0) =  m * Eigen::Matrix3d::Identity();
        M_RB.block<3,3>(0,3) = -m * Lib::Kinematics::Utils::skew(r_bg);
        M_RB.block<3,3>(3,0) =  m * Lib::Kinematics::Utils::skew(r_bg);
        M_RB.block<3,3>(3,3) =  I;

        M_A = -1 * Eigen::Vector<double,6>(Xudot,Yvdot,Zwdot,Kpdot,Mqdot,Nrdot).asDiagonal();
        M   = M_RB + M_A;
    }

    void 
    computeCoriolisMatrix(KinematicsData& data)
    {
        auto& C     = data.underwater.C;
        auto& M     = data.general.M;
        auto  vel   = data.getVelocity();
        auto  omega = data.getAngularVelocity();

        Eigen::Matrix3d M_11 = M.block<3,3>(0,0);
        Eigen::Matrix3d M_12 = M.block<3,3>(0,3);
        Eigen::Matrix3d M_21 = M.block<3,3>(3,0);
        Eigen::Matrix3d M_22 = M.block<3,3>(3,3);

        C.block<3,3>(0,0) = Eigen::Matrix3d::Zero();
        C.block<3,3>(0,3) = -Lib::Kinematics::Utils::skew(M_11*vel + M_12*omega);
        C.block<3,3>(3,0) = C.block<3,3>(0,3);
        C.block<3,3>(3,3) = -Lib::Kinematics::Utils::skew(M_21*vel + M_22*omega);
    }

    void 
    computeDampingMatrix(KinematicsData& data)
    {
        auto& uw = data.underwater;

        auto& nu     = data.nu;
        auto& D_lin  = uw.D_lin;
        auto& D_quad = uw.D_quad;
        auto& D      = uw.D;
        auto& Xu     = uw.Xu;
        auto& Yv     = uw.Yv;
        auto& Zw     = uw.Zw;
        auto& Kp     = uw.Kp;
        auto& Mq     = uw.Mq;
        auto& Nr     = uw.Nr;
        auto& Xuu    = uw.Xuu;
        auto& Yvv    = uw.Yvv;
        auto& Zww    = uw.Zww;
        auto& Kpp    = uw.Kpp;
        auto& Mqq    = uw.Mqq;
        auto& Nrr    = uw.Nrr;

        D_lin = Eigen::Vector<double,6>(Xu, Yv, Zw, Kp, Mq, Nr).transpose().asDiagonal();

        // for non-coupled motion eq. (8.10):
        D_quad = Eigen::Vector<double,6>(Xuu*std::abs(nu(0)), Yvv*std::abs(nu(1)), Zww*std::abs(nu(2)), Kpp*std::abs(nu(3)), Mqq*std::abs(nu(4)), Nrr*std::abs(nu(5))).transpose().asDiagonal();
        D = (-1*D_lin) + (-1*D_quad);
    }
    
    void 
    computeSystemMatrices(KinematicsData& data)
    {
        computeMassMatrix(data);
        computeCoriolisMatrix(data);
        computeDampingMatrix(data);
    }

    void computeUnderwaterVehicleDynamics(KinematicsData& data)
    {
        // using the dynamic equation:
        // M_RB*nu_dot + C_RB(nu) + D*nu + g(eta) = tau_R

        // INPUTS    
        // x = [eta, nu]
        //   eta = [pos, Theta]
        //       p =[x, y, z]
        //       Theta = [phi, theta, psi]
        //   nu = [vel, omega]
        //       vel = [u, v, w]
        //       omega = [p, q, r]
        // tau_RB = [X; Y; Z; K; M; N]'

        // PARAMETERS
        double g      = 9.81;

        auto& nu      = data.nu;
        auto& nu_dot  = data.nuDot;
        auto& eta     = data.eta;
        auto& eta_dot = data.etaDot;
        auto& tau_RB  = data.tau;

        auto& m       = data.general.mass;
        auto& r_bg    = data.general.r_bg;
        auto& M       = data.general.M;

        auto& B       = data.underwater.buoyancy;
        auto& r_bb    = data.underwater.r_bb;
        auto& C       = data.underwater.C;
        auto& D       = data.underwater.D;

        computeSystemMatrices(data);

        // Rotation from NED to body
        auto R = Kinematics::Utils::Rquat(Eigen::Quaterniond(data.getOrientationQuat()));
        auto T = Kinematics::Utils::Tquat(Eigen::Quaterniond(data.getOrientationQuat()));

        // buoyancy and gravity force vectors in NED
        double W = m*g;
        Eigen::Vector<double,3> f_nb = -1*Eigen::Vector<double,3>(0, 0, B).transpose();
        Eigen::Vector<double,3> f_ng = Eigen::Vector<double,3>(0, 0, W).transpose();

        auto f_g = R.transpose()*f_ng;
        auto f_b = R.transpose()*f_nb;

        Eigen::Vector<double,6> g_eta;
        g_eta.block<3,1>(0,0) = f_b + f_g;
        g_eta.block<3,1>(3,0) = r_bg.cross(f_g) + r_bb.cross(f_b);
        g_eta *= -1;

        // Dynamic equations
        Eigen::Matrix<double,7,6> J;
        J.block<3,3>(0,0) = R;
        J.block<3,3>(0,3) = Eigen::Matrix3d::Zero();
        J.block<4,3>(3,0) = Eigen::Matrix<double,4,3>::Zero();
        J.block<4,3>(3,3) = T;

        Eigen::Matrix<double,6,6> M_inv  = M.inverse();
        eta_dot = J*nu;
        nu_dot  = M_inv * (tau_RB -C*nu -D*nu -g_eta);
    }
}