#include "Axes.h"
#include <GL/gl.h>

Axes::Axes()
{
    drawAxes();
}

Axes::~Axes()
{

}

void 
Axes::drawAxes() 
{
    // Begin drawing lines
    glBegin(GL_LINES);

    // Draw X axis (Red)
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);

    // Draw Y axis (Green)
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    // Draw Z axis (Blue)
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glVertex3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);

    glEnd(); // End drawing
}