cmake_minimum_required(VERSION 3.24)
project(Lab3_3sem)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab3_3sem model/graph/Graph.h presenter/Presenter.cpp presenter/Presenter.h view/App.cpp view/App.h view/MainFrame.cpp view/MainFrame.h)

find_package(wxWidgets REQUIRED core base)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Lab3_3sem PROPERTY CXX_STANDARD 20)
endif()

if (wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    target_link_libraries(Lab3_3sem ${wxWidgets_LIBRARIES})
endif()