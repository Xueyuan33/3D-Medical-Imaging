cmake_minimum_required(VERSION 3.0)

project(ClassificationITK)

# Find ITK
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(ClassificationITK ClassificationITK.cxx)

# Link your program with the ITK libraries
target_link_libraries(ClassificationITK ${ITK_LIBRARIES})

install(TARGETS ClassificationITK
        RUNTIME DESTINATION bin)
