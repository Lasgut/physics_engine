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
        aircraftDynamics(deltaTime);
    }
    if (data_.type == "ROV")
    {
        underwaterDynamics(deltaTime);
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
    auto& m     = data_.general.mass;
    auto& r_bg  = data_.general.r_bg;
    auto& M     = data_.general.M;
    auto& I_xx  = data_.general.I_xx;
    auto& I_yy  = data_.general.I_yy;
    auto& I_zz  = data_.general.I_zz;
    auto& I_xz  = data_.general.I_xz;
    auto& M_RB  = data_.underwater.M_RB;
    auto& M_A   = data_.underwater.M_A;
    auto& Xudot = data_.underwater.Xudot;
    auto& Yvdot = data_.underwater.Yvdot;
    auto& Zwdot = data_.underwater.Zwdot;
    auto& Kpdot = data_.underwater.Kpdot;
    auto& Mqdot = data_.underwater.Mqdot;
    auto& Nrdot = data_.underwater.Nrdot;

    Eigen::Matrix3d I = Eigen::Vector<double,3>(I_xx, I_yy, I_zz).asDiagonal();
    I(0,2) = I_xz;

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
    auto& C     = data_.underwater.C;
    auto& M     = data_.general.M;
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
    auto& uw = data_.underwater;

    auto& nu     = data_.nu;
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
Kinematics::underwaterDynamics(const double deltaTime)
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

    auto& nu      = data_.nu;
    auto& nu_dot  = data_.nuDot;
    auto& eta     = data_.eta;
    auto& eta_dot = data_.etaDot;
    auto& tau_RB  = data_.tau;

    auto& m       = data_.general.mass;
    auto& r_bg    = data_.general.r_bg;
    auto& M       = data_.general.M;

    auto& B       = data_.underwater.buoyancy;
    auto& r_bb    = data_.underwater.r_bb;
    auto& C       = data_.underwater.C;
    auto& D       = data_.underwater.D;

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

    Eigen::Matrix<double,6,6> M_inv  = M.inverse();
    eta_dot = J*nu;
    nu_dot  = M_inv * (tau_RB -C*nu -D*nu -g_eta);
}


void 
Kinematics::aircraftDynamics(const double deltaTime)
{
    double g   = 9.81;
    double rho = 1.225;

    auto& nu       = data_.nu;
    auto& nu_dot   = data_.nuDot;
    auto& eta      = data_.eta;
    auto& eta_dot  = data_.etaDot;
    auto& tau      = data_.tau;

    auto& mass     = data_.general.mass;
    auto& r_bg     = data_.general.r_bg;
    auto& M        = data_.general.M;
    
    auto& ac = data_.aircraft;
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
    auto quat = Eigen::Quaterniond(data_.getOrientationQuat());
    auto R = data_.getOrientationQuat().toRotationMatrix(); // NED to body
    auto T = Tquat(quat);

    updateMassMatrix();

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
    double thrust = 1.5;
    Eigen::Vector<double,6> F;
    F << (fx+thrust), fy, fz, l, m, n;

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
