#include "QtSignalMapper.h"

#include <QPushButton>
#include <QObject>
#include <QComboBox>

QtSignalMapper::QtSignalMapper(MainWindow* window, SimulationCore* simulationCore, Visualizer* visualizer, DataPlotter* dataPlotter)
    : window_(window)
    , simulationCore_(simulationCore)
    , visualizer_(visualizer)
    , dataPlotter_(dataPlotter)
{
    QObject::connect(
        qobject_cast<QPushButton*>(window_->getPlayButton()), 
        &QPushButton::clicked,  
        this, 
        &QtSignalMapper::playButtonClicked);

    QObject::connect(
        qobject_cast<QComboBox*>(window_->getCameraModeBox()), 
        static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), 
        this, 
        &QtSignalMapper::cameraModeChanged);

    // setup signal connections
    QObject::connect(simulationCore_, &SimulationCore::entityKinematicsUpdated,
                     visualizer_,     &Visualizer::entityKinematicsUpdated);
    QObject::connect(simulationCore_, &SimulationCore::entityKinematicsUpdated,
                     dataPlotter_,    &DataPlotter::entityKinematicsUpdated);

    QObject::connect(simulationCore_, &SimulationCore::controlSystemDataUpdated,
                     dataPlotter_,    &DataPlotter::controlSystemDataUpdated);
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
    static_cast<QPushButton*>(window_->getPlayButton())->setText(settings_.simulation.isRunning ? "Stop" : "Play");
}