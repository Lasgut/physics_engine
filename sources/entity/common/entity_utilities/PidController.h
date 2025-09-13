#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#pragma once
#include "Clock.h"

class PidController
{
    public:
        PidController(const double P, const double I, const double D, const int frequency);

        double control(const double ref, const double feedback);

    private:
        double P_{0.0};
        double I_{0.0};
        double D_{0.0};

        double effort_{0};

        int   frequency_{1};
        Clock clock_;
};

#endif