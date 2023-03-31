# Simple C++ OpenGL template

A simplified template for an OpenGL program in C++. The extended version can be
found [here](https://gitlab.com/ketkev/cxx_opengl_template).

Uses CMake and [CPM](https://github.com/TheLartians/CPM.cmake) to remove the pain from downloading dependencies.

## Features

- Hassle-free usage of OpenGL since GLEW, FreeGLUT and GLM are downloaded for you
- Included code style so you don't have to think about it

## Usage

Since CPM will make sure the necessary dependencies are available, compiling this *shouldn't* require any manual
dependency installation (excluding CMake and the C++ compiler).

### Visual Studio

You can use CMake projects in Visual Studio **if** you've installed the "C++ CMake tools for Windows" component through
the Visual Studio Installer.

To use this project in Visual Studio, simply open the folder in Visual Studio. CMake should start running after a couple
of seconds.

### CLI

You first have to run this command to generate a project with CMake. This can be done with your preferred generator.

```shell
> cmake -S . -B build
```

Here the `-S` option is the path to source. The `-B` option is the path to the build directory. This is where the
compiled files will be kept.

After this, you run the build command to actually compile the progam.

```shell
> cmake --build build --target Simple_OpenGL
```

The `--build` option tells CMake to compile the code in the build directory which is passed directly after it.

### Other IDEs

This project will probably also work with other IDEs which support CMake.

## Extending this project

This project is supposed to provide a basis for you to start building your own OpenGL project off of. If you haven't
used CMake before, there are a few things you have to know to do this.

### CMake has to be told about new files

CMake has to be told explicitly which files to compile. This is stored in two variables in the `CMakeLists.txt` file and
looks a bit like this.

```cmake
set(SOURCE_FILES src/main.cpp src/my_class.cpp src/glsl.cpp)

set(HEADER_FILES include/my_class.hpp include/glsl.hpp)
```

You'll have to manually modify these two variables if you add, move, rename or remove any header or source files. While
it is technically possible for CMake to discover the files automatically, this isn't recommended because it can slow
down compilation significantly.

Some IDEs (like CLion) automatically prompt you to add new files to the `CMakeLists.txt`.

## Prerequisites

### Windows

You need to have CMake installed. You can download it through the Visual Studio Installer with the "C++ CMake tools for
Windows" component or [here](https://cmake.org/download/).

You also need to have a C++ compiler installed. An easy way to do this on Windows is to install the "Desktop development
with C++" workload through the Visual Studio Installer.

To use the Visual Studio C++ compiler in combination with CMake you also need to have a Windows SDK installed. This can
once again be done through the Visual Studio Installer.

While CPM will work without any further configuration, it is recommended to set a source caching directory to avoid
re-downloading dependencies. Instructions can be found [here](https://github.com/cpm-cmake/CPM.cmake#cpm_source_cache)

As far as I know, there *shouldn't* be any extra setup necessary for Windows. If I missed something please open an issue
or merge request.

### Linux

You need to have CMake installed

You also need to have a C++ compiler with C++-17 support installed.

While CPM will work without any further configuration, it is recommended to set a source caching directory to avoid
re-downloading dependencies. Instructions can be found [here](https://github.com/cpm-cmake/CPM.cmake#cpm_source_cache)

On Linux you'll also need opengl, X11 and XInput installed. Those can be installed
with `sudo apt install libgl1-mesa-dev libglu1-mesa-dev libx11-dev libxi-dev` on Debian/Ubuntu

## License

This template is released under the Unlicense. Enjoy!