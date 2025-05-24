# Physics Engine

## Simple physics engine based on kinematic equations.
This project presents a physics engine/simulator, based on kinematic equations. SDL is used to create the application window and openGL is used to create the 3D visualization. The kinematic/dynamic equations used is inspired by multiple [sources](#sources). See also [Usefull Documentation](#usefull-documentation) for more details. 

### Setup Instructions, Linux Ubuntu
Install [system dependencies](#system-dependencies)
```bash
sudo apt update
sudo apt install cmake libsdl2-dev libglm-dev libeigen3-dev libgl1-mesa-dev g++ nlohmann-json3-dev
```
Navigate to desired location and clone with git submodules
```bash
git clone --recurse-submodules git@github.com:Lasgut/physics_engine.git
```
Compile the project
```bash
mkdir build
cd build
cmake ..
make
```
Run program
```bash
../bin/Linux64/physics_engine
```

### Structure
Each object/entity contains a shape and kinematics. The shape is drawn in the 3D visualizer based on the calculated position and orientation. The kinematics is stored in a data container available for drawing and computation. 
Should include a figure of the design structure...

### System Dependencies
| Name | Description | Library | Version |
|:---:|:---|:---:| :---: |
| Cmake  | C++ builder                               | cmake           | |
| SDL2   | Manages application window and input      | libsdl2-dev     | |     
| GLM    | Provides mathematics functions for OpenGL | libglm-dev      | |
| Eigen3 | Supports linear algebra operations        | libeigen3-dev   | | 
| OpenGL | Supplies OpenGL for 3D rendering          | libgl1-mesa-dev | |

### Boundle Dependencies
The directory third_party includes files from external sources

| Name | Description | Source | Git submodule | Version |
| :---: | :--- | :---: | :---: | :---: |
| GLAD       | Interface to OpenGL. Generated from [here](https://gen.glad.sh/). | [GitHub](https://github.com/Dav1dde/glad)       | no  | gl 4.6 |
| STB        | Used to load height maps. For example gray scale png.             | [GitHub](https://github.com/nothings/stb)       | no  |        |
| ImGUI      | Used to create GUI within the application window.                 | [GitHub](https://github.com/ocornut/imgui)      | yes |        |
| STL Reader | Used to convert .stl to openGL vertices to render 3D models       | [GitHub](https://github.com/sreiter/stl_reader) | no  |        |

### Usefull Documentation
* [OpenGL tutorial](https://learnopengl.com/)
* [UAV sim](https://github.com/byu-magicc/mavsim_public?tab=readme-ov-file)
* [MSS toolbox](https://github.com/cybergalactic/MSS)

### Sources
* Thor I. Fossen, _Handbook of marine craft hydrodynamics and motion control_, 2nd ed, Hoboken, NJ: Wiley, 2021.
* Randal W. Beard and Timothy W. McLain, _Small Unmanned Aircraft_, Princeton University Press, November 27, 2024.
