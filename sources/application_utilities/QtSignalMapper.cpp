#include "QtSignalMapper.h"

QtSignalMapper::QtSignalMapper(QObject *parent)
    : QObject(parent)
{
}


void 
QtSignalMapper::cameraModeChanged(int index)
{
    settings_.camera.mode = static_cast<CameraMode>(index);
}


void
QtSignalMapper::playButtonClicked()
{
    settings_.simulation.isRunning = !settings_.simulation.isRunning;
}