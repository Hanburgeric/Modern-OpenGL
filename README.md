# Modern OpenGL
<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExYTY2ZmMxdHVzcWV0ZW9mZWl4Zjg1dmpzMDBmM2Zsd2lzMGNrY3NmeSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/dV4JuxzPjX4ZSe8mDu/giphy.gif"/>
</p><br>

A departure from previous projects, moving away from the usage of the deprecated, fixed function pipeline to adopt the more modern, shader-based approach.

As a result, the project shifts its focus from physics to graphics programming, with a particular focus on lighting, and more specifically, the Phong reflection model. Future plans are to implement the Blinn-Phong reflection model, and eventually, physically based rendering (PBR).

Features a simple GUI using [Dear ImGui](https://github.com/ocornut/imgui) that adds interactivity to the scene, used to display performance information, control simple physics, alter light and material properties, and toggle the skybox.

<br>

## Features
### Mesh Generation
Primitive meshes generated programmatically using mathematical equations and user-defined variables (e.g. length, radius, etc.), currently featuring cubes and tori. Smooth surface normals are automatically calculated using the generated vertex information.

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExcDJhZTd6OGE5aTN0MGtwbzh1aTR4ejJrMmU3a2FwdGpzMGp5cDhjaiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/aP81xkDnoaHy17Kxms/giphy.gif"/>
</p><br>

### Light and Material Properties
Objects change color depending the ambient, diffuse, specular values of their respective materials, as well as the color and position of lights. Currently a crude implementation of the Phong reflection model, to be replaced with the Blinn-Phong reflection model and have added to it additional features (e.g. attenuation, gamma correction, etc.) to improve realism.

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExcmJtb2N2OHNuZ3JrdDVpY3NhNnZ0N3hpYnFnazN0cmd4OHF3eTQ2bCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/LSSAgU7prd0zmsTI9H/giphy.gif"/>
</p><br>

### Simple Physics
As of now, only simulates gravity using delta time, functioning as a placeholder for future physics implementations.

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExN3l4ajBka2pzMjAwNjlwenB0cDB5cGJjbWl2eGM0bHI0cjNmcHJ3MiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Ic6scafjt8G9kLAecn/giphy.gif"/>
</p><br>

### Imported Models
External models imported using [Assimp](https://assimp.org/). While geometry is functional, shaders for these models have yet to support lighting and PBR materials.

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExOXVmMTV5MmVwbjNubWpiNTlsMGhhYzczdnYxdDk0Zzh6czl5MjhpbSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Pr2PS0AqprWVwDJk8m/giphy.gif"/>
</p><br>

### Skybox
A simple skybox implemented using a cubemap, to be used for environment mapping in the future.

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExdGlqanhwc2UxYmFmaDdjbDU1bzFxcWtjNGZ0bHRoM29nMnA5cjZjYSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Np58BqlE87u1RDbvKZ/giphy.gif"/>
</p><br>

## Build and Deployment
In the case that the .exe does not work (normally due to library linking errors), compile and run the code from Visual Studio by following the following steps:
 1. Set active solution configuration to
    <br>`Release`.
 3. Set active solution platform to
    <br>`x64`.
 5. In project properties, under `Debugging`, set `Environment` to
    <br>`PATH=../dll;%PATH$`.
 6. In project properties, under `C/C++`, set `Additional Include Directories` to
    <br>`../include;%(AdditionalIncludeDirectories)`.
 8. In project properties, under `Linker`, set `Additional Library Directories` to
    <br>`../lib;%(AdditionalLibraryDirectories)`.
 10. In project properties, under `Linker` → `Input`, set `Additional Dependencies` to
     <br>`assimp-vc141-mtd.lib;freeglut.lib;freeglutd.lib;glew32.lib;glfw3.lib;%(AdditionalDependencies)`.

<br>

## Controls
Camera
 - `MMB` + Drag : move camera.
 - `LAlt` + `MMB` + Drag : rotate camera.
 - `Scroll` : zoom camera.
<br>

## To-Do
 - Improve lighting/material to be more realistic (e.g. attenuation, gamma correction, etc.).
 - Implement Blinn-Phong reflection model.
 - Rewrite shaders for imported models such that they also support lighting.
 - Update rendering pipeline to include PBR workflow.
 - Employ environment mapping using the skybox.
 - Implement features (e.g. collision physics) from previous projects, [Pinball](https://github.com/Hanburgeric/Pinball) and [Deformable Body and Particle System Simulation](https://github.com/Hanburgeric/Deformable-Body-and-Particle-System-Simulation), using the current OpenGL infrastructure.
 - Otherwise refactoring of code to meet current standards.
<br>

## Development Environment
 - IDE : Visual Studio
 - Compiler : MSVC
 - Libraries :
   - [Assimp](https://assimp.org/)
   - [Dear ImGui](https://github.com/ocornut/imgui)
   - [GLAD](https://glad.dav1d.de/)
   - [GLFW](https://www.glfw.org/)
   - [GLM](http://glm.g-truc.net)
   - [STB](https://github.com/nothings/stb)
