cmake_minimum_required(VERSION 3.7)
project(GAME)

FILE(GLOB GAME_FILES src/*.cpp)

ADD_EXECUTABLE( ${PROJECT_NAME} ${GAME_FILES} )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../simpleton/bin)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../simpleton/vendor/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../simpleton/vendor/glad/include)

if(WIN32)
    TARGET_LINK_LIBRARIES( ${PROJECT_NAME} 
        ${CMAKE_SOURCE_DIR}/../simpleton/bin/SIMPLETON_LIB.lib
        ${CMAKE_SOURCE_DIR}/../simpleton/bin/glfw3.lib
        ${CMAKE_SOURCE_DIR}/../simpleton/bin/OpenAL32.lib
        avrt
        ole32
        winmm
        user32
    )
endif()
