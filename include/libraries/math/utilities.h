#pragma once


namespace Lib::Math::Utils
{
    inline double 
    deg2rad(const double degrees)
    {
        return degrees * M_PI / 180.0;
    }


    inline double 
    rad2deg(const double radians)
    {
        return radians * 180.0 / M_PI;
    }


    inline double 
    safeDivide(double numerator, double denominator, double defaultValue = 0.0)
    {
        return (denominator == 0.0) ? defaultValue : numerator / denominator;
    }


    inline double
    ns2sec(const double ns)
    {
        return ns / 1e9;
    }
}