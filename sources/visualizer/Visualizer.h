#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "glad/gl.h"
#include <QOpenGLWidget>
#include "visualizer_utilities/Camera.h"
#include "visualizer_utilities/ShaderHandler.h"
#include "visualizer_utilities/Light.h"
#include "objects/Floor.h"
#include "objects/Axes.h"
#include "objects/Terrain.h"
#include "shapes/Rectangle.h"
#include "ResourceHandler.h"
#include "EventState.h"
#include "Entity.h"

class Visualizer
    : public QOpenGLWidget
{
    Q_OBJECT

public:
    Visualizer(QWidget *parent = nullptr);
    
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void setResourceHandler(ResourceHandler* resourceHandler) { resourceHandler_ = resourceHandler; }

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    ResourceHandler* resourceHandler_;
    ShaderHandler    simpleShaderHandler_;
    ShaderHandler    shaderHandler_;
    ShaderHandler    terrainShaderHandler_;
    Camera*          camera_{nullptr};
    Light*           light_{nullptr};
    Axes*            axes_{nullptr};
    Terrain*         terrain_{nullptr};
    Entity*          drone_{nullptr};
    Axes*            droneCenterAxes_{nullptr};

    EventState& eventState_ = EventState::getInstance();
    QPoint lastMousePos_;

signals:
    void newData(const double x, const double y);
};

#endif // VISUALIZER_H
