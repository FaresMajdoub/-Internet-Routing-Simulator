cmake_minimum_required(VERSION 3.20)
project(Internet-Routing-Simulator)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# Fetch GoogleTest and set the timestamp to avoid policy warning
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(Internet-Routing-Simulator
        ContratException.cpp
        ContratException.h
        Routeur.cpp
        Routeur.h
        Reseau.cpp
        Reseau.h
        main.cpp
        Graphe.h
        Graphe.hpp
)

enable_testing()
add_subdirectory(tests)
