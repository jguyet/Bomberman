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
find_package(GLFW3) # FOO_INCLUDE_DIR, FOO_LIBRARIES, FOO_DIR
find_package(GLM) # FOO_INCLUDE_DIR, FOO_LIBRARIES, FOO_DIR
find_package(ASSIMP) # FOO_INCLUDE_DIR, FOO_LIBRARIES, FOO_DIR
find_package(SDL) # FOO_INCLUDE_DIR, FOO_LIBRARIES, FOO_DIR

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
	message("MACOS -----------------------------------------------------------")
	set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/macos")
	#create macos directory
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}")
		file(MAKE_DIRECTORY "${PROJECT_DIR}")
	endif()

	#GLM
	############################################################################
	if (NOT SDL2_FOUND)
		message("INSTALLATION SDL-------------------------------------------------")
		execute_process(COMMAND brew install sdl
					WORKING_DIRECTORY "${PROJECT_DIR}/")
		execute_process(COMMAND homebrew install sdl
								WORKING_DIRECTORY "${PROJECT_DIR}/")
		find_package(SDL2 REQUIRED)
		message("-----------------------------------------------------------------")
	endif()
	if (NOT EXISTS "${PROJECT_DIR}/SDL2")
		execute_process(COMMAND cp -r "${SDL2_DIR}/../../../" "SDL2"
						WORKING_DIRECTORY "${PROJECT_DIR}/")
	endif()
	link_directories(
		"${PROJECT_DIR}/SDL2"
		"${PROJECT_DIR}/SDL2/lib"
		)
	include_directories("${PROJECT_DIR}/SDL2/include")
	#GLM
	############################################################################
	if (NOT GLM_FOUND)
		message("INSTALLATION GLM-------------------------------------------------")
		execute_process(COMMAND brew install glm
					WORKING_DIRECTORY "${PROJECT_DIR}/")
		execute_process(COMMAND homebrew install glm
								WORKING_DIRECTORY "${PROJECT_DIR}/")
		find_package(GLM REQUIRED)
		message("-----------------------------------------------------------------")
	endif()
	if (NOT EXISTS "${PROJECT_DIR}/GLM")
		execute_process(COMMAND cp -r "${GLM_DIR}/../../../" "GLM"
						WORKING_DIRECTORY "${PROJECT_DIR}/")
	endif()
	link_directories(
		"${PROJECT_DIR}/GLM"
		"${PROJECT_DIR}/GLM/lib"
		)
	include_directories("${PROJECT_DIR}/GLM/include")
	#ASSIMP
	############################################################################
	if (NOT ASSIMP_FOUND)
		message("INSTALLATION ASSIMP----------------------------------------------")
		execute_process(COMMAND brew install assimp
					WORKING_DIRECTORY "${PROJECT_DIR}/")
		execute_process(COMMAND homebrew install assimp
								WORKING_DIRECTORY "${PROJECT_DIR}/")
		find_package(ASSIMP REQUIRED)
		message("-----------------------------------------------------------------")
	endif()
	if (NOT EXISTS "${PROJECT_DIR}/ASSIMP")
		execute_process(COMMAND cp -r "${ASSIMP_DIR}/../../../" "ASSIMP"
						WORKING_DIRECTORY "${PROJECT_DIR}/")
	endif()
	link_directories(
		"${PROJECT_DIR}/ASSIMP"
		"${PROJECT_DIR}/ASSIMP/lib"
		)
	include_directories("${PROJECT_DIR}/ASSIMP/include")
	#SOIL
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}/SOIL")
		message("INSTALLATION SOIL------------------------------------------------")
		execute_process(COMMAND git clone "https://github.com/alelievr/SOIL2.git" "SOIL"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
		if(NOT EXISTS "${PROJECT_DIR}/SOIL/lib")
			execute_process(COMMAND make
						WORKING_DIRECTORY ${PROJECT_DIR}/SOIL
						)
		endif()
		message("-----------------------------------------------------------------")
	endif()
		link_directories(
		  ${PROJECT_DIR}/SOIL
		)
		include_directories(${PROJECT_DIR}/SOIL/incs)
	message("-----------------------------------------------------------------")
endif()

if (WIN32)
	set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/windows")
	#create windows directory
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}")
		file(MAKE_DIRECTORY "${PROJECT_DIR}")
	endif()

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
#target_link_libraries(${PROJECT_NAME} "sdl2-config --libs SDL2_image SDL2_mixer SDL2_ttf")
target_link_libraries(${PROJECT_NAME} SDL2 glm assimp SOIL2 ${OPENGL_gl_LIBRARY} ${OPENAL_LIBRARY})

#target_link_libraries(${PROJECT_NAME} "sdl2-config --libs SDL2_image SDL2_mixer SDL2_ttf")
