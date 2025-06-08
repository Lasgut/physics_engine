#include "glad/gl.h"
#include "MainWindow.h"
#include "Visualizer.h"
#include "ResourceHandler.h"
#include "QtSignalMapper.h"

#include <QApplication>
#include <QPushButton>
#include <QObject>
#include <QComboBox>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow window;

    ResourceHandler resourceHandler(std::filesystem::path(argv[0]).parent_path());

    Visualizer *visualizer = new Visualizer(&window);

    visualizer->setResourceHandler(&resourceHandler);

    window.setVisualizerWidget(visualizer);

    // setup signal connections
    QtSignalMapper signalMapper;
    QObject::connect(
        qobject_cast<QPushButton*>(window.getPlayButton()), 
        &QPushButton::clicked,  
        &signalMapper, 
        &QtSignalMapper::playButtonClicked);

    QObject::connect(
        qobject_cast<QComboBox*>(window.getCameraModeBox()), 
        static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), 
        &signalMapper, 
        &QtSignalMapper::cameraModeChanged);

    window.show();
    return application.exec();
}