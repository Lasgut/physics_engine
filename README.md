# Physics Engine

## Simple physics engine based on kinematic equations.
This project presents a physics engine or simulator based on kinematic equations. SDL is used to create the application window, openGL to create 3D image and kinematics alters the position and orientation of objects in the visualizer.

### Setup Instructions, Linux Ubuntu
Install [dependencies](#system-dependencies)
```bash
sudo apt update
sudo apt install libsdl2-dev libglm-dev libeigen3-dev libgl1-mesa-dev
```
Clone with git submodules
```bash
git clone --recurse-submodules https://github.com/Lasgut/physics_engine.git
```
Compile the project
```bash
Cmake
```

### Structure
Each object/entity contains a shape and kinematics. The shape is drawn in the 3D visualizer based on the calculated position and orientation. The kinematics is stored in a struct available for drawing and computation. 
Should include a figure of the design structure...

### System Dependencies
| Name | Description | Library |
|:---:|:---|:---:|
| SDL2   | Manages application window and input      | libsdl2-dev     |     
| GLM    | Provides mathematics functions for OpenGL | libglm-dev      |
| Eigen3 | Supports linear algebra operations        | libeigen3-dev   |
| OpenGL | Supplies OpenGL for 3D rendering          | libgl1-mesa-dev |

### Boundle Dependencies
The directory third_party includes files from external sources

| Name | Description | Source | Git submodule |
| :---: | :--- | :---: | :---: |
| GLAD  | Interface to OpenGL. Generated from [here](https://gen.glad.sh/). | [GitHub](https://github.com/Dav1dde/glad)  | no  |
| STB   | Used to load height maps. For example gray scale png.             | [GitHub](https://github.com/nothings/stb)  | no  |
| ImGUI | Used to create GUI within the application window.                 | [GitHub](https://github.com/ocornut/imgui) | yes |

### Usefull documentation
* [OpenGL tutorial](https://learnopengl.com/)
