cmake_minimum_required (VERSION 3.8)

set(INJECTOR_ENGINE_VERSION 0.1.0)
project (injector_engine VERSION ${INJECTOR_ENGINE_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(deps/glad)
add_subdirectory(deps/glfw)
add_subdirectory(deps/glm)

set(INJECTOR_ENGINE_RESOURCE_FILES
    shaders/unlit.frag
    shaders/unlit.vert
PARENT_SCOPE)

foreach(FILE ${INJECTOR_ENGINE_RESOURCE_FILES})
    configure_file(resources/${FILE} resources/${FILE} COPYONLY)
endforeach(FILE)

add_library(${PROJECT_NAME} STATIC
    source/buffer.cpp
    source/camera.cpp
    source/engine.cpp
    source/entity.cpp
    source/material.cpp
    source/mesh.cpp
    source/persp_camera.cpp
    source/primitive.cpp
    source/renderer.cpp
    source/shader.cpp
    source/transform.cpp
    source/unlit_material.cpp
    source/vert_mesh.cpp
    source/vertex_array.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${GLAD_SOURCE_DIR}/include
    ${GLFW_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glad
    glfw
    glm::glm
)
