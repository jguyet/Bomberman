################################################################################
# Project settings
################################################################################
find_package(Git REQUIRED)

cmake_minimum_required( VERSION 3.2.2 )
set(project_name "Bomberman")
project(${project_name})

#BUILD DIRECTORY
set(CMAKE_CURRENT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

################################################################################
# Load external_libraries
################################################################################
#glfw
execute_process(COMMAND git clone "https://github.com/glfw/glfw.git"
				WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/
				)
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE STRING "" FORCE)
set(GLFW_INSTALL        OFF CACHE STRING "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/glfw)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/glfw/include/GLFW)

#glm
execute_process(COMMAND git clone "https://github.com/g-truc/glm.git"
				WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/
				)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/glm)

execute_process(COMMAND git clone "https://github.com/alelievr/SOIL2.git"
				WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/
				)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/SOIL2)
execute_process(COMMAND make WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/SOIL2)

#find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

################################################################################
# Build executables
################################################################################

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

file(GLOB_RECURSE CLIENT_SRC srcs/*.cpp)

add_executable(${project_name} ${CLIENT_SRC})

include_directories(${project_name} includes ${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/SOIL2/incs ${GLEW_INCLUDE_DIRS})

target_link_libraries(${project_name} glfw ${CMAKE_CURRENT_SOURCE_DIR}/external_libraries/SOIL2/libSOIL2.so ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES})
