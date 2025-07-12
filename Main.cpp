#include "glad/gl.h"
#include "MainWindow.h"
#include "Visualizer.h"
#include "ResourceHandler.h"
#include "QtSignalMapper.h"
#include "DataPlotter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow window;

    ResourceHandler resourceHandler(std::filesystem::path(argv[0]).parent_path());

    Visualizer *visualizer = new Visualizer(&window);

    visualizer->setResourceHandler(&resourceHandler);

    window.setVisualizerWidget(visualizer);

    DataPlotter dataPlotter(&window);

    // setup signal connections
    QObject::connect(visualizer,  &Visualizer::newData,
                     &dataPlotter, &DataPlotter::newData);

    QtSignalMapper signalMapper(&window);

    window.show();
    return application.exec();
}