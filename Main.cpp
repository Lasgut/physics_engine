#include "glad/gl.h"
#include "MainWindow.h"
#include "Visualizer.h"
#include "ResourceHandler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow window;

    ResourceHandler resourceHandler(std::filesystem::path(argv[0]).parent_path());

    Visualizer *visualizer = new Visualizer(&window);

    visualizer->setResourceHandler(&resourceHandler);


    window.setVisualizerWidget(visualizer);

    window.show();
    return application.exec();
}