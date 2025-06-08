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

class Visualizer
    : public QOpenGLWidget
{
    Q_OBJECT

public:
    Visualizer(QWidget *parent = nullptr);
    
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
};

#endif // VISUALIZER_H
