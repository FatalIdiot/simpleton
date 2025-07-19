cmake_minimum_required(VERSION 3.7)
project(SIMPLETON_LIB)

FILE(GLOB SIMPLETON_FILES
    src/*.cpp src/*.h
    src/graphics/*.cpp src/graphics/*.h
    src/audio/*.cpp src/audio/*.h
    src/inputs/*.cpp src/inputs/*.h
    src/resources/*.cpp src/resources/*.h
    vendor/glad/glad.c
)

add_library(${PROJECT_NAME} STATIC 
        ${SIMPLETON_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glad/include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendor/glfw/glfw3.lib)