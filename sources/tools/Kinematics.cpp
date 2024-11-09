#include "Kinematics.h"
#include "KinematicsData.h"
#include <Eigen/Dense>
#include <glm/glm.hpp>
#include <iostream>

Kinematics::Kinematics()
{
}

Kinematics::~Kinematics()
{
}

void 
Kinematics::eulerIntegration(float deltaTime) 
{
    data_.position        += data_.velocity * deltaTime;
    data_.velocity        += data_.acceleration * deltaTime;
    data_.orientation     += data_.angularVelocity * deltaTime;
    data_.angularVelocity += data_.angularAcceleration *deltaTime;
}

void 
Kinematics::setPosition(const Eigen::Vector3<float>& pos) 
{
    data_.position = pos;
}

void 
Kinematics::setVelocity(const Eigen::Vector3<float>& vel) 
{
    data_.velocity = vel;
}

void 
Kinematics::setOrientation(const Eigen::Vector3<float>& orient) 
{
    data_.orientation = orient;
}

void 
Kinematics::setMass(float mass) 
{
    data_.mass = mass;
}

const Eigen::Vector3<float>& 
Kinematics::getPosition() const 
{
    return data_.position;
}

const Eigen::Vector3<float>& 
Kinematics::getVelocity() const 
{
    return data_.velocity;
}

const Eigen::Vector3<float>& 
Kinematics::getOrientation() const 
{
    return data_.orientation;
}

float 
Kinematics::getMass() const 
{
    return data_.mass;
}

const glm::vec3
Kinematics::getPositionAsGlm() const
{
    glm::vec3 pos;
    pos.x = data_.position.x();
    pos.y = data_.position.y();
    pos.z = data_.position.z();
    return pos;
}

const glm::vec3
Kinematics::getOrientationAsGlm() const
{
    glm::vec3 ori;
    ori.x = data_.orientation.x();
    ori.y = data_.orientation.y();
    ori.z = data_.orientation.z();
    return ori;
}


void
Kinematics::systemMatrices()
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
    // tau_RB = [X; Y; Z; K; M; N]

    // PARAMETERS
    float g   = data_.gravity;
    float m   = 11.5;
    auto r_bg = Eigen::Vector<float,3>(0, 0, 0.02);
    auto r_bb = Eigen::Vector<float,3>(0, 0, 0);
    auto eta_dot = Eigen::Vector<float,6>(0.0,0.0,0.0,0.0,0.0,0.0);
    auto nu_dot  = Eigen::Vector<float,6>(0,0,0,0,0,0);

    // State vector
    auto pos   = data_.position;
    auto Theta = data_.orientation;
    auto vel   = data_.velocity;
    auto omega = data_.angularVelocity;
    Eigen::Vector<float,6> nu;
    nu.block<3,1>(0,0) = vel;
    nu.block<3,1>(3,0) = omega;

    // Rotation from NED to body
    auto phi   = Theta(0);
    auto theta = Theta(1);
    auto psi   = Theta(2);
    auto R     = Rzyx(phi, theta, psi);
    auto T     = Tzyx(phi, theta);

    // MASS MATRIX
    float I_xx = 0.16;
    float I_yy = 0.16;
    float I_zz = 0.16;
    auto I = Eigen::Vector<float,3>(I_xx, I_yy, I_zz).asDiagonal();

    Eigen::Matrix<float,6,6> M_RB;
    M_RB.block<3,3>(0,0) =  m * Eigen::Matrix3f::Identity();
    M_RB.block<3,3>(0,3) = -m * skew(r_bg);
    M_RB.block<3,3>(3,0) =  m * skew(r_bg);
    M_RB.block<3,3>(3,3) =  I;
    
    // Added mass matrix
    float Xudot = -5.5;
    float Yvdot = -12.7;
    float Zwdot = -14.57;
    float Kpdot = -0.12;
    float Mqdot = -0.12;
    float Nrdot = -0.12;

    Eigen::Matrix<float,6,6> M_A = -1 * Eigen::Vector<float,6>(Xudot,Yvdot,Zwdot,Kpdot,Mqdot,Nrdot).asDiagonal();
    auto M = M_RB + M_A;
    auto M_11 = M.block<3,3>(0,0);
    auto M_12 = M.block<3,3>(0,3);
    auto M_21 = M.block<3,3>(3,0);
    auto M_22 = M.block<3,3>(3,3);

    // Coriolis–Centripetal Matrix
    Eigen::Matrix<float,6,6> C;
    C.block<3,3>(0,0) = Eigen::Matrix3f::Zero();
    C.block<3,3>(0,3) = -skew(M_11*vel + M_12*omega);
    C.block<3,3>(3,0) = C.block<3,3>(0,3);
    C.block<3,3>(3,3) = -skew(M_21*vel + M_22*omega);

    // Damping parameters (Sandøy, 2016, Sec. 4.3.3)
    // Linear damping 
    float Xu = -4.03;
    float Yv = -6.22;
    float Zw = -5.18;
    float Kp = -0.07;
    float Mq = -0.07;
    float Nr = -0.07; // only this was identified; K_p, M_q set equal

    // Quadratic damping
    float Xuu = -18.18;
    float Yvv = -21.66;
    float Zww = -36.99;
    float Kpp = -1.55;
    float Mqq = -1.55;
    float Nrr = -1.55; // only this was identified; K_pp, M_qq set equal

    // for non-coupled motion eq. (8.10):
    Eigen::Matrix<float,6,6> D;
    auto D_lin  = Eigen::Vector<float,6>(Xu, Yv, Zw, Kp, Mq, Nr).transpose().asDiagonal();
    auto D_quad = Eigen::Vector<float,6>(Xuu*std::abs(nu(0)), Yvv*std::abs(nu(1)), 
    Zww*std::abs(nu(2)), Kpp*std::abs(nu(3)), Mqq*std::abs(nu(4)), Nrr*std::abs(nu(5))).transpose().asDiagonal();
    D = (-1*D_lin) + (-1*D_quad);

    // EXTERNAL FORCES
    float W = m*g;
    float B = 112.8;
    // buoyancy and gravity force vectors in NED
    Eigen::Vector<float,3> f_nb = -1*Eigen::Vector<float,3>(0, 0, B).transpose();
    Eigen::Vector<float,3> f_ng = Eigen::Vector<float,3>(0, 0, W).transpose();

    auto f_g = R.transpose()*f_ng;
    auto f_b = R.transpose()*f_nb;

    Eigen::Vector<float,6> g_eta;
    g_eta.block<3,1>(0,0) = f_b + f_g;
    g_eta.block<3,1>(3,0) = r_bg.cross(f_g) + r_bb.cross(f_b);
    g_eta *= -1;

    // Dynamic equations
    Eigen::Matrix<float,6,6> J;
    J.block<3,3>(0,0) = R;
    J.block<3,3>(0,3) = Eigen::Matrix3f::Zero();
    J.block<3,3>(3,0) = Eigen::Matrix3f::Zero();
    J.block<3,3>(3,3) = T;

    Eigen::Vector<float,6> tau_RB  = Eigen::Vector<float,6>(0.1,0,0,0,0,0);
    eta_dot = J*nu;
    nu_dot  = M.inverse() * (tau_RB -C*nu -D*nu -g_eta);

    data_.velocity            = eta_dot.block<3,1>(0,0); 
    data_.angularVelocity     = eta_dot.block<3,1>(3,0);
    data_.acceleration        = nu_dot.block<3,1>(0,0);
    data_.angularAcceleration = nu_dot.block<3,1>(3,0);
}

Eigen::Matrix<float,3,3>
Kinematics::skew(const Eigen::Vector<float,3>& v) 
{
    Eigen::Matrix<float,3,3> skewMat;
    skewMat <<    0, -v(2),  v(1),
               v(2),     0, -v(0),
              -v(1),  v(0),     0;
    return skewMat;
}

Eigen::Matrix<float,3,3>
Kinematics::Rzyx(float phi, float theta, float psi) 
{
    // Compute trigonometric functions
    float cphi = cos(phi);
    float sphi = sin(phi);
    float cth = cos(theta);
    float sth = sin(theta);
    float cpsi = cos(psi);
    float spsi = sin(psi);

    // Construct rotation matrix
    Eigen::Matrix<float,3,3> R;
    R << cpsi * cth, -spsi * cphi + cpsi * sth * sphi, spsi * sphi + cpsi * cphi * sth,
         spsi * cth, cpsi * cphi + sphi * sth * spsi, -cpsi * sphi + sth * spsi * cphi,
         -sth, cth * sphi, cth * cphi;

    return R;
}

Eigen::Matrix<float,3,3>
Kinematics::Tzyx(float phi, float theta) 
{
    // Compute trigonometric functions
    float cphi = cos(phi);
    float sphi = sin(phi);
    float cth = cos(theta);
    float sth = sin(theta);

    // Handle singularity when cth = 0 (i.e., theta = +-90 degrees)
    if (cth == 0) {
        throw std::runtime_error("Tzyx is singular for theta = +-90 degrees");
    }

    // Construct transformation matrix
    Eigen::Matrix<float,3,3> T;
    T << 1, sphi * sth / cth, cphi * sth / cth,
         0, cphi, -sphi,
         0, sphi / cth, cphi / cth;

    return T;
}