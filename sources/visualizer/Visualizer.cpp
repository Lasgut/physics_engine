#include "Visualizer.h"
#include "glad/gl.h"
#include <QOpenGLContext>
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>
#include <QTimer>


static void* qtGetProcAddress(const char* proc)
{
    return (void*) QOpenGLContext::currentContext()->getProcAddress(proc);
}


Visualizer::Visualizer(QWidget *parent, ResourceHandler* resourceHandler)
    : QOpenGLWidget(parent)
    , resourceHandler_(resourceHandler)
{
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Visualizer::update));
    timer->start(16); // ~60 FPS (1000ms / 60 ≈ 16ms)
    setFocusPolicy(Qt::StrongFocus);
}


void Visualizer::initializeGL()
{
    if (!gladLoadGL((GLADloadfunc)qtGetProcAddress)) 
    {
        std::cerr << "ERROR: Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    const char* glVersion = (const char*)glGetString(GL_VERSION);
    if (glVersion == nullptr) 
    {
        std::cerr << "ERROR: OpenGL context is not initialized or active!" << std::endl;
        exit(1);
    }
    std::cout << "OpenGL Version: " << glVersion << std::endl;

    // Basic OpenGL setup
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // TODO: Initialize other resources (shaders, buffers, etc.)
    auto& shaders    = resourceHandler_->getFiles().shaders;
    auto& heightMaps = resourceHandler_->getFiles().heightMaps;
    auto& meshes     = resourceHandler_->getFiles().meshes; 

    droneMesh_       = new StlMesh(meshes.fpvDrone);
    camera_          = new Camera();
    light_           = new Light();
    axes_            = new Axes();
    terrain_         = new Terrain(heightMaps.icelandHeightMapPath.c_str());
    droneCenterAxes_ = new Axes(0.1f);

    simpleShaderHandler_.init(shaders.simpleVertexShaderPath.c_str(), shaders.simpleFragmentShaderPath.c_str());
    shaderHandler_.init(shaders.vertexShaderPath.c_str(), shaders.fragmentShaderPath.c_str());
    terrainShaderHandler_.init( 
        shaders.terrainVertexShaderPath.c_str(), 
        shaders.terrainFragmentShaderPath.c_str(),
        shaders.terrainGeometryShaderPath.c_str()
    );
}


void 
Visualizer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera_->update(dronePosition_, droneOrientation_);

    terrainShaderHandler_.use(*camera_);
    terrain_->update(terrainShaderHandler_);

    shaderHandler_.use(*camera_);
    light_->update(shaderHandler_, *camera_);

    simpleShaderHandler_.use(*camera_);
    droneCenterAxes_->setPosition(dronePosition_);
    droneCenterAxes_->setOrientation(droneOrientation_);
    droneCenterAxes_->update(simpleShaderHandler_);

    shaderHandler_.use(*camera_);
    droneMesh_->draw(shaderHandler_, dronePosition_, droneOrientation_);

    camera_->setLookAt(dronePosition_);

    simpleShaderHandler_.use(*camera_);
    axes_->update(simpleShaderHandler_);
}


void 
Visualizer::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}


void 
Visualizer::entityKinematicsUpdated(int entityId, Eigen::Vector3d position, Eigen::Quaterniond orientation)
{
    if (entityId == 1 && droneMesh_) 
    {
        droneOrientation_ = glm::quat(orientation.w(), orientation.x(), orientation.y(), orientation.z());
        dronePosition_    = glm::vec3(position.x(), position.y(), position.z());
    }
}


void 
Visualizer::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        eventState_.mouse.leftButtonDown = true;
    else if (event->button() == Qt::RightButton)
        eventState_.mouse.rightButtonDown = true;
}


void 
Visualizer::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        eventState_.mouse.leftButtonDown = false;
    else if (event->button() == Qt::RightButton)
        eventState_.mouse.rightButtonDown = false;
}


void 
Visualizer::mouseMoveEvent(QMouseEvent* event)
{
    eventState_.mouse.x = event->pos().x();
    eventState_.mouse.y = event->pos().y();

    if (eventState_.mouse.leftButtonDown)
    {
        QPoint rel = event->pos() - lastMousePos_;
        if (std::abs(rel.x()) < 100 && std::abs(rel.y()) < 100)
        {
            eventState_.mouse.xRel = rel.x();
            eventState_.mouse.yRel = rel.y();
        }
    }

    lastMousePos_ = event->pos();
}


void 
Visualizer::wheelEvent(QWheelEvent* event)
{
    eventState_.mouse.wheelRel = event->angleDelta().y() / 120;
}


void 
Visualizer::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
    {
        eventState_.keyboard.ctrl = true;
    }
    if (event->key() == Qt::Key_Up)
    {
        eventState_.keyboard.up = true;
    }
    if (event->key() == Qt::Key_Down)
    {
        eventState_.keyboard.down = true;
    }
    if (event->key() == Qt::Key_Left)
    {
        eventState_.keyboard.left = true;
    }
    if (event->key() == Qt::Key_Right)
    {
        eventState_.keyboard.right = true;
    }
    if (event->key() == Qt::Key_Space)
    {
        eventState_.keyboard.space = true;
    }
}


void 
Visualizer::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
    {
        eventState_.keyboard.ctrl = false;
    }
    if (event->key() == Qt::Key_Up)
    {
        eventState_.keyboard.up = false;
    }
    if (event->key() == Qt::Key_Down)
    {
        eventState_.keyboard.down = false;
    }
    if (event->key() == Qt::Key_Left)
    {
        eventState_.keyboard.left = false;
    }
    if (event->key() == Qt::Key_Right)
    {
        eventState_.keyboard.right = false;
    }
    if (event->key() == Qt::Key_Space)
    {
        eventState_.keyboard.space = false;
    }
}
