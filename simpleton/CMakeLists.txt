cmake_minimum_required(VERSION 3.7)
project(SIMPLETON_LIB)

FILE(GLOB SIMPLETON_FILES
    src/*.cpp
    src/graphics/*.cpp
    src/audio/*.cpp
    src/inputs/*.cpp
    src/resources/*.cpp
    vendor/glad/glad.c
)

add_library(${PROJECT_NAME} STATIC 
        ${SIMPLETON_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glad/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/openal-soft/include)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendor/glfw/glfw3.lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendor/OpenAL32.lib)
endif()