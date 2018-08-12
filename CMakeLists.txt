cmake_minimum_required(VERSION 3.1)

project(zhabotinsky) #Executable name

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11") #Banderas de compilación

set(SOURCES
    main.cpp
    pingpong.h
    pingpong.cpp
    shader_util.h
    shader_util.cpp)

#Archivos que son parte de la configuración pero no de la compilación
configure_file(vertex_shader.glsl vertex_shader.glsl COPYONLY) #Copiar con ese nombre al directorio del proyecto
configure_file(fragment_shader.glsl fragment_shader.glsl COPYONLY)
configure_file(test_shader.glsl test_shader.glsl COPYONLY)

add_executable(${PROJECT_NAME} ${SOURCES}) #Produce un ejecutable de nombre PROJECT_NAME compuesto de SOURCES

if(UNIX)
    target_link_libraries(${PROJECT_NAME} GL)
    target_link_libraries(${PROJECT_NAME} GLEW)
    target_link_libraries(${PROJECT_NAME} glfw)
endif(UNIX)

if(WIN32)
    include_directories(D:/Documents/C++/OpenGL/DependenciesMinGW/include/)

    target_link_libraries(${PROJECT_NAME} opengl32)

    find_library(GLEW_LIB libglew32.dll HINTS D:/Documents/C++/OpenGL/DependenciesMinGW/lib/)
    target_link_libraries(${PROJECT_NAME} ${GLEW_LIB})

    find_library(GLFW_LIB glfw3dll HINTS D:/Documents/C++/OpenGL/DependenciesMinGW/lib/)
    target_link_libraries(${PROJECT_NAME} ${GLFW_LIB})
endif(WIN32)
