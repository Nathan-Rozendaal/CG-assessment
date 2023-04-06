# Set minimum version of CMake for this project
cmake_minimum_required(VERSION 3.15)

# Tells CMake to store compiled files in the `lib` and `bin` folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create a project
project(Simple_OpenGL VERSION 1.0.0 LANGUAGES CXX)

# Prevent in-source builds. This clutters the source directory.
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR “In-source builds not allowed! Create a build directory and run CMake from there. ”)
endif ()

# Includes a CMake package manager
include(cmake/CPM.cmake)

# Downloads and sets up the necessary dependencies for OpenGL

# FreeGLUT
CPMAddPackage(
        NAME FreeGLUT
        GITHUB_REPOSITORY dcnieho/FreeGLUT
        VERSION 3.2.2
        OPTIONS "FREEGLUT_BUILD_DEMOS OFF" "FREEGLUT_BUILD_SHARED_LIBS OFF"
        EXCLUDE_FROM_ALL YES
)

# GLEW
CPMAddPackage(
        NAME glew
        URL https://github.com/nigels-com/glew/releases/download/glew-2.0.0/glew-2.0.0.zip
        VERSION 2.0.0
        DOWNLOAD_ONLY True
)

# GLEW keeps the CMake file in a non-standard directory so we need to manually add it after downloading
if (glew_ADDED)
    set(BUILD_UTILS OFF CACHE BOOL "Build glew utilities")
    add_subdirectory("${glew_SOURCE_DIR}/build/cmake" "${glew_BINARY_DIR}" EXCLUDE_FROM_ALL)
endif ()

# GLM
CPMAddPackage(
        NAME glm
        GITHUB_REPOSITORY g-truc/glm
        GIT_TAG 0.9.6.3
        EXCLUDE_FROM_ALL YES
)
# Saves the files for this project to two variables
set(SOURCE_FILES
        src/main.cpp
        src/glsl.cpp
        src/IBL.cpp 
        src/AnimationBehaviours.cpp)

set(HEADER_FILES
        include/glsl.hpp
        include/shader.h
        include/Mesh.h
        include/Model.h
        include/camera.h
        include/stb_image.h
        include/IBL.h
        include/AnimationBehaviours.h)

# Create an executable called `Simple_OpenGL` with the files we declared earlier
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Compiles the `Simple_OpenGL` executable with C++-17. While C++-20 is out, C++-17 has better compiler support.
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Declares the include directories for the `Simple_OpenGL` target.
# This would be more useful when writing a library but I've included it for when you want (or need) to use headers.
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${FreeGLUT_SOURCE_DIR}/include
        ${glew_SOURCE_DIR}/include
        libs/assimp-5.2.5/include
        )
set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS  ON)
set(ASSIMP_BUILD_STATIC_LIB ON)
add_subdirectory(libs/assimp-5.2.5)


# Links the required OpenGL libraries into our executable
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        freeglut_static
        glew_s
        assimp
        )

# Copy resources to build folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/OBJs DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Checks and enabled link time optimisation if it's available for your generator and compiler.
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)
if (ipo_supported)
    set(INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()

# Enables CCache if you have it installed. This caches unchanged compilations and makes it faster.
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif ()