cmake_minimum_required (VERSION 3.8)

set(GLAD_VERSION 0.1.33)
project (glad VERSION ${GLAD_VERSION} LANGUAGES C)

add_library(${PROJECT_NAME}_debug STATIC
    src/glad_debug.c
)

target_include_directories(${PROJECT_NAME}_debug PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_library(${PROJECT_NAME}_release STATIC
    src/glad_release.c
)

target_include_directories(${PROJECT_NAME}_release PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
