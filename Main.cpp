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

    QtSignalMapper signalMapper(&window, &simulationCore, visualizer, &dataPlotter);

    window.show();

    std::thread simulationThread([&]()
    {
        pthread_setname_np(pthread_self(), "SimulationCore");
        while (true) 
        {
            simulationCore.update();
        }
    });

    std::thread plottingThread([&]()
    {
        pthread_setname_np(pthread_self(), "Plotting");
        while (true) 
        {
            dataPlotter.updatePlots();
        }
    });

    return application.exec();
}