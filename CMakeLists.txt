cmake_minimum_required (VERSION 3.8)
project (injector_engine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(deps/glfw)

add_library(${PROJECT_NAME} STATIC
    src/component.cpp
    src/engine.cpp
    src/entity.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${GLFW_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
