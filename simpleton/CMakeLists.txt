cmake_minimum_required(VERSION 3.7)
project(SIMPLETON_LIB)

FILE(GLOB SIMPLETON_FILES ogl/*.cpp ogl/*.h
    src/*.cpp src/*.h
    vendor/glad/glad.c
)

add_library(${PROJECT_NAME} STATIC 
        ${SIMPLETON_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glad/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendor/glfw/glfw3.lib)