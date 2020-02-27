cmake_minimum_required (VERSION 3.8)

set(GLAD_VERSION 0.1.33)
project (glad VERSION ${GLAD_VERSION} LANGUAGES C)


add_library(${PROJECT_NAME} STATIC
    src/glad.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
