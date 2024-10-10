# Modern OpenGL (Readme WIP)
<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExYTVvOTZwMHA3ejd0d2lzN2h5NHhvdmtwZWlhM3Bxb3o3cHVzN2Y3YiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/At0gGRg8mntzr3S1C8/giphy.gif"/>
</p><br>

A departure from previous projects, moving away from the usage of the deprecated, fixed function pipeline to adopt the more modern, shader-based approach.

As a result, the project shifts its focus from physics to graphics programming, with a particular focus on lighting, and more specifically, the Phong reflection model. Future plans are to extend this to be the Blinn-Phong reflection model, and eventually, physically based rendering (PBR).

<br>

## Features
### Mathematically Generated Meshes (w/ Manually Calculated Surface Normals)
???

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExenV3bWV1MzRvZDZtaGtsZGp0c3UwYzJwcmlzbDU1d29yMWowYmZ6bCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Or2sPBUWa1bJbqjRKz/giphy.gif"/>
</p><br>

### Light and Material Properties
???

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExenV3bWV1MzRvZDZtaGtsZGp0c3UwYzJwcmlzbDU1d29yMWowYmZ6bCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Or2sPBUWa1bJbqjRKz/giphy.gif"/>
</p><br>

### Simple Physics
???

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExenV3bWV1MzRvZDZtaGtsZGp0c3UwYzJwcmlzbDU1d29yMWowYmZ6bCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Or2sPBUWa1bJbqjRKz/giphy.gif"/>
</p><br>

### Imported Meshes
??? Assimp

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExenV3bWV1MzRvZDZtaGtsZGp0c3UwYzJwcmlzbDU1d29yMWowYmZ6bCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Or2sPBUWa1bJbqjRKz/giphy.gif"/>
</p><br>

### Skybox
???

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExenV3bWV1MzRvZDZtaGtsZGp0c3UwYzJwcmlzbDU1d29yMWowYmZ6bCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Or2sPBUWa1bJbqjRKz/giphy.gif"/>
</p><br>

### GUI
A simple GUI that adds interactivity to the scene. Used to display performance information, control simple physics, alter light and material properties, and toggle the skybox.

<p align=center>
<img width=720 src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExenV3bWV1MzRvZDZtaGtsZGp0c3UwYzJwcmlzbDU1d29yMWowYmZ6bCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Or2sPBUWa1bJbqjRKz/giphy.gif"/>
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
     <br>`assimp-vc141-mtd.lib;glfw3.lib;%(AdditionalDependencies)`.

<br>

## Controls
Camera
 - `MMB` + Drag : move camera.
 - `LAlt` + `MMB` + Drag : rotate camera.
 - `Scroll` : zoom camera.
<br>

## To-Do
 - ???
 - Update lighting/material to be more ??? (e.g. attenuation), ??? Blinn-Phong ???.
 - Update imported models to also ??? lighting.
 - ??? environment mapping.
 - Update rendering pipeline to accept physically based rendering (PBR) models.
 - Implement features (e.g. collision physics) from previous projects, [Pinball](https://github.com/Hanburgeric/Pinball) and [Deformable Body and Particle System Simulation](https://github.com/Hanburgeric/Deformable-Body-and-Particle-System-Simulation), using the current OpenGL infrastructure.
 - Otherwise refactoring of code to meet current standards.
<br>

## Development Environment
 - IDE : Visual Studio
 - Compiler : MSVC
 - Libraries :
   - [ASSIMP](https://assimp.org/)
   - [GLAD](https://glad.dav1d.de/)
   - [GLFW](https://www.glfw.org/)
   - [IMGUI](https://github.com/ocornut/imgui)
   - [STB](https://github.com/nothings/stb)
