cmake_minimum_required(VERSION 3.24)
project(Programmation)

set(CMAKE_CXX_STANDARD 11)

add_executable(Programmation main.cpp
        Intervalle.cpp
        Intervalle.h interpolation_hermite.cpp interpolation_hermite.h generation_inversion.cpp generation_inversion.h division.cpp division.h utilitaires.cpp utilitaires.h generation_aleatoire.cpp generation_aleatoire.h)
