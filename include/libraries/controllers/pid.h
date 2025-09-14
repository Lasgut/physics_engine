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
                auto gainI = I_ * integrator_;
                if (antiWindupLimit_ != 0.0)
                {
                    gainI = std::clamp(gainI, -antiWindupLimit_, antiWindupLimit_);
                    if (abs(gainI) < antiWindupLimit_ ||
                       (gainI >= antiWindupLimit_  && error < 0) ||
                       (gainI <= -antiWindupLimit_ && error > 0))
                    {
                        integrator_ += error;
                    }
                }

                double effort = P_ * error  + gainI + D_ * (error - previousError_);
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
