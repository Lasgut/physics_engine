#pragma once


namespace Lib::Math::Utils
{
    inline double safeDivide(double numerator, double denominator, double defaultValue = 0.0)
    {
        return (denominator == 0.0) ? defaultValue : numerator / denominator;
    }
}