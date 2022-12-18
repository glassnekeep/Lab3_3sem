cmake_minimum_required(VERSION 3.24)
project(Lab3_3sem)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab3_3sem main.cpp model/graph/Graph.h presenter/Presenter.cpp presenter/Presenter.h view/App.cpp view/App.h view/MainFrame.cpp view/MainFrame.h)
