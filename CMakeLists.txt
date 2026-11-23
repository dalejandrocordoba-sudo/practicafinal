cmake_minimum_required(VERSION 3.16)

project(practica5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(practica5 main.cpp
    simulacion.h
    particula.h
    particula.cpp
    simulacion.cpp
    motorfisico.h
    motorfisico.cpp
    evento.h
    obstaculo.h
    obstaculo.cpp)

include(GNUInstallDirs)
install(TARGETS practica5
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
