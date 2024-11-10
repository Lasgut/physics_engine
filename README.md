# Physics Engine

## Simple physics engine based on kinematic equations.
This project presents a physics engine or simulator based on kinematic equations. SDL is used to create the application window, openGL to create 3D image and kinematics alters the position and orientation of objects in the visualizer.

### Setup Instructions, Linux
'''bash
git clone --recurse-submodules https://github.com/Lasgut/physics_engine.git
'''

### Dependencies
* SDL2
* OpenGL
* glm
* Eigen3

### Structure
Each object/entity contains a shape and kinematics. The shape is drawn in the 3D visualizer based on the calculated position and orientation. The kinematics is stored in a struct available for drawing and computation. 
Should include a figure of the design structure...

### Third Party Sources
The directory third_party includes files from external sources. A description of each source, its origin and usage follows,
#### glad  
* interface to openGL
* generated using https://gen.glad.sh/
* the generator source code https://github.com/Dav1dde/glad
#### stb 
* used to load height maps. For example gray scale .png
* originates from git repository https://github.com/nothings/stb
#### imgui (git submodule)
* used to create GUI within the application window
* originates from git repository https://github.com/ocornut/imgui
