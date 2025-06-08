#include "QtSignalMapper.h"

QtSignalMapper::QtSignalMapper(QObject *parent)
    : QObject(parent)
{
}

void
QtSignalMapper::playButtonClicked(bool checked)
{
    settings_.simulation.isRunning = !settings_.simulation.isRunning;
}