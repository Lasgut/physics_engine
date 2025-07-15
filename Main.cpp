#include "glad/gl.h"
#include "MainWindow.h"
#include "Visualizer.h"
#include "ResourceHandler.h"
#include "QtSignalMapper.h"
#include "DataPlotter.h"
#include "SimulationCore.h"

#include <QApplication>
#include <thread>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow window;

    ResourceHandler resourceHandler(std::filesystem::path(argv[0]).parent_path());
    SimulationCore  simulationCore(&resourceHandler);
    DataPlotter     dataPlotter(&window);

    Visualizer* visualizer = new Visualizer(&window, &resourceHandler);
    window.setVisualizerWidget(visualizer);

    // setup signal connections
    QObject::connect(&simulationCore, &SimulationCore::entityKinematicsUpdated,
                     visualizer,      &Visualizer::entityKinematicsUpdated);
    QObject::connect(&simulationCore, &SimulationCore::entityKinematicsUpdated,
                     &dataPlotter,    &DataPlotter::entityKinematicsUpdated);

    QtSignalMapper signalMapper(&window);

    window.show();

    std::thread simulationThread([&]()
    {
        while (true) 
        {
            simulationCore.update();
        }
    });

    return application.exec();
}