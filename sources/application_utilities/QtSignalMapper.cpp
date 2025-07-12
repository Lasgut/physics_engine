#include "QtSignalMapper.h"

#include <QPushButton>
#include <QObject>
#include <QComboBox>

QtSignalMapper::QtSignalMapper(QObject *parent)
    : QObject(parent)
{
    window_ = static_cast<MainWindow*>(parent);

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