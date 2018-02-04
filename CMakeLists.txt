################################################################################
# Project settings
################################################################################
cmake_minimum_required( VERSION 3.2.2 )
set(PROJECT_NAME "Bomberman")
project(${PROJECT_NAME})

#BUILD DIRECTORY
set(CMAKE_CURRENT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)

################################################################################
# APPLE INSTALL LIBS
################################################################################

#version c++11
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

#create lib directory
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../lib")
	file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../lib")
endif()

if (APPLE)
	set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/macos")
	#create macos directory
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}")
		file(MAKE_DIRECTORY "${PROJECT_DIR}")
	endif()

	#GLFW
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/GLFW")
		execute_process(COMMAND git clone "https://github.com/glfw/glfw.git" "GLFW"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
	endif()
		set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
		set(GLFW_BUILD_TESTS    OFF CACHE STRING "" FORCE)
		add_subdirectory(${PROJECT_DIR}/GLFW)
		include_directories(${PROJECT_DIR}/GLFW/include/GLFW)

	#GLM
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/GLM")
		execute_process(COMMAND git clone "https://github.com/g-truc/glm.git" "GLM"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
	endif()
		add_subdirectory(${PROJECT_DIR}/GLM)
		include_directories(${PROJECT_DIR}/GLM)

	#ASSIMP
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/ASSIMP")
		execute_process(COMMAND git clone "https://github.com/assimp/assimp.git" "ASSIMP"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
	endif()
	if(NOT EXISTS "${PROJECT_DIR}/ASSIMP/lib")
		execute_process(COMMAND cmake -G "Unix Makefiles"
					WORKING_DIRECTORY ${PROJECT_DIR}/ASSIMP
					)
		execute_process(COMMAND make
					WORKING_DIRECTORY ${PROJECT_DIR}/ASSIMP
					)
	endif()
		link_directories(
		  ${PROJECT_DIR}/ASSIMP
		  ${PROJECT_DIR}/ASSIMP/lib/
		  ${PROJECT_DIR}/ASSIMP/samples/DevIL/lib/
		)
		include_directories(${PROJECT_DIR}/ASSIMP/include)

	#SOIL
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/SOIL")
		execute_process(COMMAND git clone "https://github.com/paralin/soil.git" "SOIL"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
	endif()
		add_subdirectory(${PROJECT_DIR}/SOIL)
		include_directories(${PROJECT_DIR}/SOIL)
endif()

if (WIN32)
	set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/windows")
	#create windows directory
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}")
		file(MAKE_DIRECTORY "${PROJECT_DIR}")
	endif()

	#GLFW
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/GLFW")
		execute_process(COMMAND git clone "https://github.com/glfw/glfw.git" "GLFW"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
	endif()
		set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
		set(GLFW_BUILD_TESTS    OFF CACHE STRING "" FORCE)
		add_subdirectory(${PROJECT_DIR}/GLFW)
		include_directories(${PROJECT_DIR}/GLFW/include/GLFW)

	#GLM
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/GLM")
		execute_process(COMMAND git clone "https://github.com/g-truc/glm.git" "GLM"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
	endif()
		add_subdirectory(${PROJECT_DIR}/GLM)
		include_directories(${PROJECT_DIR}/GLM)

	#ASSIMP
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/ASSIMP")
		execute_process(COMMAND git clone "https://github.com/assimp/assimp.git" "ASSIMP"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
	endif()
		add_subdirectory(${PROJECT_DIR}/ASSIMP)
		include_directories(${PROJECT_DIR}/ASSIMP/include)

	#SOIL
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/SOIL")
		execute_process(COMMAND git clone "https://github.com/paralin/soil.git" "SOIL"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
	endif()
		add_subdirectory(${PROJECT_DIR}/SOIL)
		include_directories(${PROJECT_DIR}/SOIL)

endif()

if (UNIX AND NOT APPLE)
	set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/linux")
	#create linux directory
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}")
		file(MAKE_DIRECTORY "${PROJECT_DIR}")
	endif()

	#GLFW
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/GLFW")
		execute_process(COMMAND git clone "https://github.com/glfw/glfw.git" "GLFW"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
	endif()
		set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
		set(GLFW_BUILD_TESTS    OFF CACHE STRING "" FORCE)
		add_subdirectory(${PROJECT_DIR}/GLFW)
		include_directories(${PROJECT_DIR}/GLFW/include/GLFW)

	#GLM
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/GLM")
		execute_process(COMMAND git clone "https://github.com/g-truc/glm.git" "GLM"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
	endif()
		add_subdirectory(${PROJECT_DIR}/GLM)
		include_directories(${PROJECT_DIR}/GLM)

	#ASSIMP
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/ASSIMP")
		execute_process(COMMAND git clone "https://github.com/assimp/assimp.git" "ASSIMP"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
	endif()
	if(NOT EXISTS "${PROJECT_DIR}/ASSIMP/lib")
		execute_process(COMMAND cmake -G "Unix Makefiles"
					WORKING_DIRECTORY ${PROJECT_DIR}/ASSIMP
					)
		execute_process(COMMAND make
					WORKING_DIRECTORY ${PROJECT_DIR}/ASSIMP
					)
	endif()
		link_directories(
		  ${PROJECT_DIR}/ASSIMP
		  ${PROJECT_DIR}/ASSIMP/lib/
		  ${PROJECT_DIR}/ASSIMP/samples/DevIL/lib/
		)
		include_directories(${PROJECT_DIR}/ASSIMP/include)

	#SOIL
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/SOIL")
		execute_process(COMMAND git clone "https://github.com/paralin/soil.git" "SOIL"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
	endif()
		add_subdirectory(${PROJECT_DIR}/SOIL)
		include_directories(${PROJECT_DIR}/SOIL)
endif()

################################################################################
# Build executables
################################################################################

file(GLOB_RECURSE CLIENT_SRC srcs/*.cpp)

add_executable(${PROJECT_NAME} ${CLIENT_SRC})

include_directories(${PROJECT_NAME} includes)

target_link_libraries(${PROJECT_NAME} glfw glm assimp soil ${OPENGL_gl_LIBRARY} ${OPENAL_LIBRARY})
