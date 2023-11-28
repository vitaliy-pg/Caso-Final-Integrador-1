find_package(json11 REQUIRED)
include_directories(${json11_INCLUDE_DIRS})

add_executable(Caso-Final-Integrador-1 tiny-lisp.cpp)
target_link_libraries(tu_programa ${json11_LIBRARIES})