cmake_minimum_required(VERSION 3.1)
project(zhabotinsky) #Executable name

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(SOURCES main.cpp shader_util.h shader_util.cpp) #Banderas de compilación

#Archivos que son parte de la configuración pero no de la compilación
configure_file(vertex_shader.glsl vertex_shader.glsl COPYONLY) #Copiar con ese nombre al directorio del proyecto
configure_file(fragment_shader.glsl fragment_shader.glsl COPYONLY)

add_executable(${PROJECT_NAME} ${SOURCES}) #Produce un ejecutable de nombre PROJECT_NAME compuesto de SOURCES

if(UNIX)
    target_link_libraries(${PROJECT_NAME} GL)
    target_link_libraries(${PROJECT_NAME} GLEW)
    target_link_libraries(${PROJECT_NAME} glfw)
endif(UNIX)
