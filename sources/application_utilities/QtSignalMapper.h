#ifndef QT_SIGNAL_MAPPER_H
#define QT_SIGNAL_MAPPER_H

#include <QPushButton>
#include <QObject>
#include <QComboBox>

#include "Settings.h"
#include "MainWindow.h"
#include "DataPlotter.h"
#include "SimulationCore.h"
#include "Visualizer.h"

class QtSignalMapper
    : public QObject
{
    Q_OBJECT

public:
    QtSignalMapper(MainWindow* window, SimulationCore* simulationCore, Visualizer* visualizer, DataPlotter* dataPlotter);

public slots:
    void playButtonClicked();
    void cameraModeChanged(int index);

private:
    Settings&       settings_        = Settings::getInstance();
    MainWindow*     window_          = nullptr;
    SimulationCore* simulationCore_  = nullptr;
    Visualizer*     visualizer_      = nullptr;
    DataPlotter*    dataPlotter_     = nullptr;
};

#endif // QT_SIGNAL_MAPPER_H