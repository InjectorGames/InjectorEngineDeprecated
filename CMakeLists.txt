cmake_minimum_required (VERSION 3.8)

set(INJECTOR_ENGINE_VERSION 0.1.0)
project (injector_engine VERSION ${INJECTOR_ENGINE_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(deps/glad)
add_subdirectory(deps/glfw)
add_subdirectory(deps/glm)

set(INJECTOR_ENGINE_RESOURCE_FILES
    fonts/jetbrains_mono/bold.ttf
    fonts/jetbrains_mono/bold_italic.ttf
    fonts/jetbrains_mono/extra_bold.ttf
    fonts/jetbrains_mono/extra_bold_italic.ttf
    fonts/jetbrains_mono/italic.ttf
    fonts/jetbrains_mono/medium.ttf
    fonts/jetbrains_mono/medium_italic.ttf
    fonts/jetbrains_mono/regular.ttf

    shaders/ambient.frag
    shaders/ambient.vert
    shaders/diffuse.frag
    shaders/diffuse.vert

    images/logo_16.png
    images/logo_32.png
    images/logo_48.png
PARENT_SCOPE)

foreach(FILE ${INJECTOR_ENGINE_RESOURCE_FILES})
    configure_file(resources/${FILE} resources/${FILE} COPYONLY)
endforeach(FILE)

add_library(${PROJECT_NAME} STATIC
    source/ambient_material.cpp
    source/buffer.cpp
    source/camera.cpp
    source/diffuse_material.cpp
    source/engine.cpp
    source/entity.cpp
    source/font.cpp
    source/image.cpp
    source/material.cpp
    source/mesh.cpp
    source/opengl_window.cpp
    source/perspective_camera.cpp
    source/primitive.cpp
    source/renderer.cpp
    source/shader.cpp
    source/texture.cpp
    source/texture_2d.cpp
    source/transform.cpp
    source/vertex_array.cpp
    source/vertex_attribute.cpp
    source/window.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${GLAD_SOURCE_DIR}/include
    ${GLFW_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/deps/stb
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glad_debug
    glad_release
    glfw
    glm::glm
)
