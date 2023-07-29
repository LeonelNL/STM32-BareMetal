cmake_minimum_required(VERSION 3.20)

project("Digital_Input" C CXX ASM)

include(cmake/st-project.cmake)

# Agregar la ruta de la carpeta "Inc" para las cabeceras
include_directories(Inc)

add_executable(${PROJECT_NAME})
add_st_target_properties(${PROJECT_NAME})

# Agregar la carpeta "Inc" como una ubicación para las cabeceras
target_include_directories(${PROJECT_NAME} PRIVATE Inc)
