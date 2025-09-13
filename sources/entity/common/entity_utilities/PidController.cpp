#include "PidController.h"

PidController::PidController(const double P, const double I, const double D, const int frequency)
    : P_(P)
    , I_(I)
    , D_(D)
    , frequency_(frequency)
{
}

double PidController::control(const double ref, const double feedback)
{
    // if (!clock_.rateLimit(frequency_)) 
    // {
    //     return effort_;
    // }
    // clock_.setPreviousTime();

    double effort_ = (ref - feedback)*P_;
    return effort_;
}
