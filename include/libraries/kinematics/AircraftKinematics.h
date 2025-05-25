#pragma once

#include "KinematicsData.h"
#include "Utilities.h"
#include <Eigen/Dense>

namespace Lib::Kinematics::Aircraft
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

        Eigen::Matrix3d I = Eigen::Vector<double,3>(I_xx, I_yy, I_zz).asDiagonal();
        I(0,2) = I_xz;

        M.block<3,3>(0,0) =  m * Eigen::Matrix3d::Identity();
        M.block<3,3>(0,3) = -m * Lib::Kinematics::Utils::skew(r_bg);
        M.block<3,3>(3,0) =  m * Lib::Kinematics::Utils::skew(r_bg);
        M.block<3,3>(3,3) =  I;
    }

    void 
    computeAircraftDynamics(KinematicsData& data)
    {
        double g   = 9.81;
        double rho = 1.225;

        auto& nu       = data.nu;
        auto& nu_dot   = data.nuDot;
        auto& eta      = data.eta;
        auto& eta_dot  = data.etaDot;
        auto& tau      = data.tau;

        auto& mass     = data.general.mass;
        auto& r_bg     = data.general.r_bg;
        auto& M        = data.general.M;
        
        auto& ac = data.aircraft;
        auto& S        = ac.S;
        auto& CL_0     = ac.CL_0;
        auto& CL_alpha = ac.CL_alpha;
        auto& CL_q     = ac.CL_q;
        auto& CY_0     = ac.CY_0;
        auto& CY_beta  = ac.CY_beta;
        auto& CY_p     = ac.CY_p;
        auto& CY_r     = ac.CY_r;
        auto& CD_0     = ac.CD_0;
        auto& CD_alpha = ac.CD_alpha;
        auto& CD_q     = ac.CD_q;
        auto& Cm_0     = ac.Cm_0;
        auto& Cm_alpha = ac.Cm_alpha;
        auto& Cm_q     = ac.Cm_q;
        auto& Cl_0     = ac.Cl_0;
        auto& Cl_beta  = ac.Cl_beta;
        auto& Cl_p     = ac.Cl_p;
        auto& Cl_r     = ac.Cl_r;
        auto& Cn_0     = ac.Cn_0;
        auto& Cn_beta  = ac.Cn_beta;
        auto& Cn_p     = ac.Cn_p;
        auto& Cn_r     = ac.Cn_r;
        auto& b        = ac.b;
        auto& c        = ac.c;

        // Orientation and transformation matrices
        auto quat = Eigen::Quaterniond(data.getOrientationQuat());
        auto R = quat.toRotationMatrix(); // NED to body
        auto T = Kinematics::Utils::Tquat(quat);

        computeMassMatrix(data);

        // Airspeed in body frame
        Eigen::Vector3d v_body = nu.head<3>();
        double V_a = v_body.norm();

        // Angle of attack: alpha = atan2(w, u)
        double u = v_body(0); // forward
        double v = v_body(1); // side
        double w = v_body(2); // vertical
        double alpha = std::atan2(w, u);
        double beta  = std::asin(v / V_a); // side slip angle

        // Aerodynamic coefficients
        double CL = CL_0 + CL_alpha * alpha;
        double CD = CD_0 + CD_alpha * alpha;

        // Body-axis force coefficients
        double CX   = -CD   * std::cos(alpha) + CL   * std::sin(alpha);
        double CX_q = -CD_q * std::cos(alpha) + CL_q * std::sin(alpha);
        double CZ   = -CD   * std::sin(alpha) - CL   * std::cos(alpha);
        double CZ_q = -CD_q * std::sin(alpha) - CL_q * std::cos(alpha);

        // Dynamic pressure
        double K1 = 0.5 * rho * V_a * V_a * S;
        double K2 = c / (2*V_a);
        double K3 = b / (2*V_a);

        // Aerodynamic forces
        auto& p = nu(3);
        auto& q = nu(4);
        auto& r = nu(5);
        double fx = K1*(CX   + CX_q*K2*q); 
        double fy = K1*(CY_0 + CY_beta*beta + CY_p*K3*p + CY_r*K3*r); 
        double fz = K1*(CZ   + CZ_q*K2*q);
        double l  = K1*b*(Cl_0 + Cl_beta*beta   + Cl_p*K3*p + Cl_r*K3*r);
        double m  = K1*c*(Cm_0 + Cm_alpha*alpha + Cm_q*K2*q);
        double n  = K1*b*(Cn_0 + Cn_beta*beta   + Cn_p*K3*p + Cn_r*K3*r);

        // Add to torque (Z-axis torque -> Yaw)
        Eigen::Vector<double,6> F;
        F << fx, fy, fz, l, m, n;

        // Gravity in body frame
        double W = mass * g;
        Eigen::Vector3d f_ng(0, 0, W); // Gravity in NED
        Eigen::Vector3d f_g = R.transpose() * f_ng; // to body frame
        Eigen::Vector<double,6> g_eta;
        g_eta.segment<3>(0) = f_g;
        g_eta.segment<3>(3) = r_bg.cross(f_g);

        // State derivative (nu_dot and eta_dot)
        Eigen::Matrix<double,7,6> J;
        J.block<3,3>(0,0) = R;
        J.block<3,3>(0,3) = Eigen::Matrix3d::Zero();
        J.block<4,3>(3,0) = Eigen::Matrix<double,4,3>::Zero();
        J.block<4,3>(3,3) = T;

        eta_dot = J * nu;
        Eigen::Matrix<double,6,6> M_inv = M.inverse();
        nu_dot = M_inv * (tau + F + g_eta);
    }
}