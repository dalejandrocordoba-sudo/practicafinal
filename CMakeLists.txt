cmake_minimum_required(VERSION 3.16)
project(laboratorio_final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(motor STATIC
    evento.h
    particula.h
    particula.cpp
    obstaculo.h
    obstaculo.cpp
    motorfisico.h
    motorfisico.cpp
    gestorarchivos.h
    gestorarchivos.cpp
)
target_include_directories(motor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(juego STATIC
    juegologica.h
    juegologica.cpp
)
target_include_directories(juego PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(juego PUBLIC motor)

add_executable(SimulacionConsola
    main_consola.cpp
)
target_link_libraries(SimulacionConsola PRIVATE motor)

enable_testing()
add_executable(test_juego
    test_juego.cpp
)
target_link_libraries(test_juego PRIVATE juego)
add_test(NAME motor_y_juego COMMAND test_juego)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets QUIET)
if(QT_FOUND)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    add_executable(JuegoEstrategia
        main_qt.cpp
        juegowindow.h
        juegowindow.cpp
        juegowindow.ui
    )
    target_link_libraries(JuegoEstrategia PRIVATE juego Qt${QT_VERSION_MAJOR}::Widgets)
else()
    message(WARNING "Qt no encontrado: se compilan solo la simulación de consola y las pruebas.")
endif()