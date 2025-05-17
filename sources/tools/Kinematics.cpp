#include "Kinematics.h"
#include "KinematicsData.h"
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
        data_.gravity  = jsonData["gravity"];
        data_.mass     = jsonData["mass"];
        data_.buoyancy = jsonData["buoyancy"];
        auto r_bg      = jsonData.at("centerOfGravity");
        data_.r_bg     = Eigen::Vector<double,3>(r_bg[0], r_bg[1], r_bg[2]);
        auto r_bb      = jsonData.at("centerOfBuoyancy");
        data_.r_bb     = Eigen::Vector<double,3>(r_bb[0], r_bb[1], r_bb[2]);

        auto inertia = jsonData.at("inertia");
        data_.I_xx = inertia["I_xx"];
        data_.I_yy = inertia["I_yy"];
        data_.I_zz = inertia["I_zz"];

        data_.Xudot = jsonData["added_mass"]["Xudot"];
        data_.Yvdot = jsonData["added_mass"]["Yvdot"];
        data_.Zwdot = jsonData["added_mass"]["Zwdot"];
        data_.Kpdot = jsonData["added_mass"]["Kpdot"];
        data_.Mqdot = jsonData["added_mass"]["Mqdot"];
        data_.Nrdot = jsonData["added_mass"]["Nrdot"];

        data_.Xu = jsonData["linear_damping"]["Xu"];
        data_.Yv = jsonData["linear_damping"]["Yv"];
        data_.Zw = jsonData["linear_damping"]["Zw"];
        data_.Kp = jsonData["linear_damping"]["Kp"];
        data_.Mq = jsonData["linear_damping"]["Mq"];
        data_.Nr = jsonData["linear_damping"]["Nr"];
        
        data_.Xuu = jsonData["quadratic_damping"]["Xuu"];
        data_.Yvv = jsonData["quadratic_damping"]["Yvv"];
        data_.Zww = jsonData["quadratic_damping"]["Zww"];
        data_.Kpp = jsonData["quadratic_damping"]["Kpp"];
        data_.Mqq = jsonData["quadratic_damping"]["Mqq"];
        data_.Nrr = jsonData["quadratic_damping"]["Nrr"];
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
    data_.mass = mass;
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


double 
Kinematics::getMass() const 
{
    return data_.mass;
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
Kinematics::update(Eigen::Vector<double,6> controlForces)
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

    // PARAMETERS
    auto& g       = data_.gravity;
    auto& m       = data_.mass;
    auto& B       = data_.buoyancy;
    auto& r_bg    = data_.r_bg;
    auto& r_bb    = data_.r_bb;
    auto& M       = data_.M;
    auto& C       = data_.C;
    auto& D       = data_.D;
    auto& nu      = data_.nu;
    auto& nu_dot  = data_.nuDot;
    auto& eta     = data_.eta;
    auto& eta_dot = data_.etaDot;

    updateSystemMatrices();

    // Rotation from NED to body
    auto R = Rquat(Eigen::Quaterniond(data_.getOrientationQuat()));
    auto T = Tquat(Eigen::Quaterniond(data_.getOrientationQuat()));

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

    Eigen::Vector<double,6>   tau_RB = controlForces;
    Eigen::Matrix<double,6,6> M_inv  = M.inverse();
    eta_dot = J*nu;
    nu_dot  = M_inv * (tau_RB -C*nu -D*nu -g_eta);

    eulerIntegration(deltaTime);

    Eigen::Vector3d eulerAngles = data_.getOrientationQuat().toRotationMatrix().eulerAngles(0, 1, 2);
    if (clockDebug_.rateLimit(2))
    {
        clockDebug_.setPreviousTime();
        std::cout << "Control Forces:  " << controlForces.transpose() << std::endl;
        std::cout << "Position:        " << data_.getPosition().transpose() << std::endl;
        std::cout << "Orientation:     " << eulerAngles.transpose() << std::endl;
        std::cout << "velocity:        " << data_.getVelocity().transpose() << std::endl;
        std::cout << "angularVelocity: " << data_.getAngularVelocity().transpose() << std::endl;
        std::cout << "eta:             " << data_.eta.transpose() << std::endl;
        std::cout << "nu:              " << data_.nu.transpose() << std::endl;
    }
}


void 
Kinematics::updateSystemMatrices()
{
    updateMassMatrix();
    updateCoriolisMatrix();
    updateDampingMatrix();
}

void 
Kinematics::updateMassMatrix()
{
    auto& m     = data_.mass;
    auto& r_bg  = data_.r_bg;
    auto& M_RB  = data_.M_RB;
    auto& M_A   = data_.M_A;
    auto& M     = data_.M;
    auto& I_xx  = data_.I_xx;
    auto& I_yy  = data_.I_yy;
    auto& I_zz  = data_.I_zz;
    auto& Xudot = data_.Xudot;
    auto& Yvdot = data_.Yvdot;
    auto& Zwdot = data_.Zwdot;
    auto& Kpdot = data_.Kpdot;
    auto& Mqdot = data_.Mqdot;
    auto& Nrdot = data_.Nrdot;

    Eigen::Matrix3d I = Eigen::Vector<double,3>(I_xx, I_yy, I_zz).asDiagonal();

    M_RB.block<3,3>(0,0) =  m * Eigen::Matrix3d::Identity();
    M_RB.block<3,3>(0,3) = -m * skew(r_bg);
    M_RB.block<3,3>(3,0) =  m * skew(r_bg);
    M_RB.block<3,3>(3,3) =  I;

    M_A = -1 * Eigen::Vector<double,6>(Xudot,Yvdot,Zwdot,Kpdot,Mqdot,Nrdot).asDiagonal();
    M   = M_RB + M_A;
}


void 
Kinematics::updateCoriolisMatrix()
{
    auto& C     = data_.C;
    auto& M     = data_.M;
    auto  vel   = data_.getVelocity();
    auto  omega = data_.getAngularVelocity();

    Eigen::Matrix3d M_11 = M.block<3,3>(0,0);
    Eigen::Matrix3d M_12 = M.block<3,3>(0,3);
    Eigen::Matrix3d M_21 = M.block<3,3>(3,0);
    Eigen::Matrix3d M_22 = M.block<3,3>(3,3);

    C.block<3,3>(0,0) = Eigen::Matrix3d::Zero();
    C.block<3,3>(0,3) = -skew(M_11*vel + M_12*omega);
    C.block<3,3>(3,0) = C.block<3,3>(0,3);
    C.block<3,3>(3,3) = -skew(M_21*vel + M_22*omega);
}


void 
Kinematics::updateDampingMatrix()
{
    auto& D_lin  = data_.D_lin;
    auto& D_quad = data_.D_quad;
    auto& D      = data_.D;
    auto& nu     = data_.nu;
    auto& Xu     = data_.Xu;
    auto& Yv     = data_.Yv;
    auto& Zw     = data_.Zw;
    auto& Kp     = data_.Kp;
    auto& Mq     = data_.Mq;
    auto& Nr     = data_.Nr;
    auto& Xuu    = data_.Xuu;
    auto& Yvv    = data_.Yvv;
    auto& Zww    = data_.Zww;
    auto& Kpp    = data_.Kpp;
    auto& Mqq    = data_.Mqq;
    auto& Nrr    = data_.Nrr;

    D_lin = Eigen::Vector<double,6>(Xu, Yv, Zw, Kp, Mq, Nr).transpose().asDiagonal();

    // for non-coupled motion eq. (8.10):
    D_quad = Eigen::Vector<double,6>(Xuu*std::abs(nu(0)), Yvv*std::abs(nu(1)), Zww*std::abs(nu(2)), Kpp*std::abs(nu(3)), Mqq*std::abs(nu(4)), Nrr*std::abs(nu(5))).transpose().asDiagonal();
    D = (-1*D_lin) + (-1*D_quad);
}


Eigen::Matrix<double,3,3>
Kinematics::skew(const Eigen::Vector<double,3>& v) 
{
    Eigen::Matrix<double,3,3> skewMat;
    skewMat <<    0, -v(2),  v(1),
               v(2),     0, -v(0),
              -v(1),  v(0),     0;
    return skewMat;
}


Eigen::Matrix<double,3,3>
Kinematics::Rzyx(double phi, double theta, double psi) 
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


Eigen::Matrix<double,3,3>
Kinematics::Tzyx(double phi, double theta) 
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


Eigen::Matrix<double, 3, 3> 
Kinematics::Rquat(const Eigen::Quaterniond &q)
{
    constexpr double tol = 1e-1;
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


Eigen::Matrix<double, 4, 3> 
Kinematics::Tquat(const Eigen::Quaterniond &q)
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
