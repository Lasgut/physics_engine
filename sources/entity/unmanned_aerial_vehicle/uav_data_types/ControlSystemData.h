#define CONTROLSYSTEMDATA_H
#ifdef CONTROLSYSTEMDATA_H

#pragma once

namespace UAV
{
struct ControlSystemData
{
    double timeStamp{0.0};
    double desiredPitch{0.0};
    double desiredAltitude{0.0};
};
}

#endif