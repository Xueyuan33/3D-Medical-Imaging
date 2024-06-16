cmake_minimum_required(VERSION 3.10)

project(KMeans3DVisualizer)

# Find ITK.
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# Uncomment if VTK is also used for visualization.
# find_package(VTK REQUIRED)
# include(${VTK_USE_FILE})

# Define the executable.
add_executable(KMeans3DVisualizer KMeans3DVisualizer.cxx)

# Link libraries.
target_link_libraries(KMeans3DVisualizer ${ITK_LIBRARIES})
# Uncomment if VTK is also used for visualization.
# target_link_libraries(KMeans3DVisualizer ${VTK_LIBRARIES})

# Specify C++ standard.
set_target_properties(KMeans3DVisualizer PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
