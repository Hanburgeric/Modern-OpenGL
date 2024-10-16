# Modern OpenGL
<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExNjlrOW10ZW8wczI5dGM3dmhoeW9qbnlqaHdqdXQwY3Z2NTMyY2s0OSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/gVnmQhqu71xDhvJ3Dn/giphy.gif"/>
</p><br>

A departure from previous projects, moving away from the usage of the deprecated, fixed function pipeline to adopt the more modern, shader-based approach.

As a result, the project shifts its focus from physics to graphics programming, with a particular focus on lighting, and more specifically, the Phong reflection model. Future plans are to implement the Blinn-Phong reflection model, and eventually, physically based rendering (PBR).

Features a simple GUI using [Dear ImGui](https://github.com/ocornut/imgui) that adds interactivity to the scene, used to display performance information, control simple physics, alter light and material properties, and toggle the skybox.

<br>

## Features
### Mesh Generation
Primitive meshes generated programmatically using mathematical equations and user-defined variables (e.g. length, radius, etc.), currently featuring cubes and tori. Smooth surface normals are automatically calculated using the generated vertex information.

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExbTZjajI4amNqNDRqMWV1NzYwM2d0a2NraHd0eXc0YmV4MXAydnltNiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/vct7bRqAfq92yDumBC/giphy.gif"/>
</p><br>

### Light and Material Properties
Objects change color depending the ambient, diffuse, specular values of their respective materials, as well as the color and position of lights. Currently a crude implementation of the Phong reflection model, to be replaced with the Blinn-Phong reflection model and have added to it additional features (e.g. attenuation, gamma correction, etc.) to improve realism.

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExdWUyazhoZW56amZ4MXl5czNnMm16OW1zMWVpd29tNGh5ejFqdnJ5cCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/6P9KmUb2O7ifJxIjrK/giphy.gif"/>
</p><br>

### Simple Physics
As of now, only simulates gravity using delta time, functioning as a placeholder for future physics implementations.

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExMmlrcXhwMDh1YzQydWczaXJsMXpyeGw4bnJqODNiNm1hdGp4ZnRpYSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/QsD8jG4dNj03YQZ1nQ/giphy.gif"/>
</p><br>

### Imported Models
External models imported using [Assimp](https://assimp.org/). While geometry is functional, shaders for these models have yet to support lighting and PBR materials.

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExeWVoOGlhZnRpYmFkemVuYXo4bHBueTlkYjFqZ2wxaHl0aXc2Mzc2NSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/gnwFY08YeVDIph58Y5/giphy.gif"/>
</p><br>

### Skybox
A simple skybox implemented using a cubemap, to be used for environment mapping in the future.

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExa2Nndm00MGltaWZ6MGVtMjIwajgzM2Y4aTJleGFhd2VveDdrdGVwbCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/dzwd0789cmHqTTCsMa/giphy.gif"/>
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
 - `LMB` + Drag : move camera.
 - `RMB` + Drag : rotate camera.
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
