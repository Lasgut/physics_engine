#ifndef PID_H
#define PID_H

#pragma once

#include "Clock.h"

namespace Lib::Controller
{

    class PID
    {
        public:
            PID(const double P, const double I, const double D, const double antiWindupLimit=0.0)
                : P_(P)
                , I_(I)
                , D_(D)
                , antiWindupLimit_(antiWindupLimit)
            {
            }

            double control(const double ref, const double feedback)
            {
                auto error = ref - feedback;
                return computePidEffort(error);
            }

            double control(const double error)
            {
                return computePidEffort(error);
            }

        private:
            double computePidEffort(const double error)
            {
                // Proportional term
                double P_term = P_ * error;

                // Derivative term
                double D_term = D_ * (error - previousError_);

                // Integrator update with anti-windup
                integrator_ += error; // accumulate first

                if (antiWindupLimit_ > 0.0)
                {
                    // clamp integrator to avoid excessive buildup
                    integrator_ = std::clamp(integrator_, -antiWindupLimit_, antiWindupLimit_);
                }

                // Compute effort
                double effort = P_term + I_ * integrator_ + D_term;

                // Save error for next derivative computation
                previousError_ = error;

                return effort;
            }

            double P_{0.0};
            double I_{0.0};
            double D_{0.0};

            double integrator_{0.0};
            double previousError_{0.0};
            double antiWindupLimit_{0.0};
        };

}

#endif
