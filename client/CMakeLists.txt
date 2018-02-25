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
	message("(CMAKE INSTALLATION FOR APPLE):\r\n")
	set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib")

	find_path(BREW_DIR brew HINTS ENV HOME)
	message("homebrew directory : ${BREW_DIR}")
	set(BIN_BREW "${BREW_DIR}/brew")
	message("homebrew binary    : ${BIN_BREW}")

	#create macos directory
	############################################################################
	if(NOT EXISTS "${PROJECT_DIR}")
		file(MAKE_DIRECTORY "${PROJECT_DIR}")
	endif()

	#GLM
	############################################################################
	message("\r\nINSTALLATION SDL2------------------------------------------------\r\n")
	execute_process(COMMAND ${BIN_BREW} install sdl2
							WORKING_DIRECTORY "${PROJECT_DIR}/")
	find_package(SDL2 REQUIRED)
	link_directories("${SDL2_DIR}/../../../lib")
	include_directories(${SDL2_INCLUDE_DIR})
	message("${SDL2_INCLUDE_DIR}")
	message("${SDL2_DIR}/../../../lib")
	# sdl2_mixer sdl2_image
	############################################################################
	execute_process(COMMAND ${BIN_BREW} install sdl2_ttf
				WORKING_DIRECTORY "${PROJECT_DIR}/")
	find_path(SDL2_TTF_INCLUDE_DIR SDL2/SDL_ttf.h
				  HINTS
				    ENV HOME
				    ${SDL2_DIR}
					${BREW_DIR}
				  PATH_SUFFIXES SDL2
	                # path suffixes
	                include/SDL2 include)
	message(${SDL2_TTF_INCLUDE_DIR})
	include_directories(${SDL2_TTF_INCLUDE_DIR})
	find_path(SDL2_TTF_LIB_DIR libSDL2_ttf.a HINTS ${BREW_DIR}/../lib)
	message("${SDL2_TTF_LIB_DIR}")
	link_directories("${SDL2_TTF_LIB_DIR}")

	execute_process(COMMAND ${BIN_BREW} install sdl2_image
				WORKING_DIRECTORY "${PROJECT_DIR}/")
	execute_process(COMMAND homebrew install sdl2_image
							WORKING_DIRECTORY "${PROJECT_DIR}/")
	find_path(SDL2_IMAGE_INCLUDE_DIR SDL2/SDL_image.h
				  HINTS
				    ENV HOME
				    ${SDL2_DIR}
					${BREW_DIR}
				  PATH_SUFFIXES SDL2
	                # path suffixes
	                include/SDL2 include)
	message(${SDL2_IMAGE_INCLUDE_DIR})
	include_directories(${SDL2_IMAGE_INCLUDE_DIR})
	find_path(SDL2_IMAGE_LIB_DIR libSDL2_image.a HINTS ${BREW_DIR}/../lib)
	message("${SDL2_IMAGE_LIB_DIR}")
	link_directories("${SDL2_IMAGE_LIB_DIR}")

	#GLM
	############################################################################
	message("\r\nINSTALLATION GLM-------------------------------------------------\r\n")
	execute_process(COMMAND ${BIN_BREW} install glm
				WORKING_DIRECTORY "${PROJECT_DIR}/")
	find_package(GLM REQUIRED)
	link_directories("${GLM_DIR}/../../../lib")
	find_path(GLM_INCLUDE_DIR glm/glm.hpp
				  HINTS
				    ENV HOME
				    ${GLM_DIR}
					${BREW_DIR}
				  PATH_SUFFIXES glm
	                # path suffixes
	                include/glm include)
	message("${GLM_INCLUDE_DIR}")
	message("${GLM_DIR}/../../../lib")
	include_directories("${GLM_INCLUDE_DIR}")
	#ASSIMP
	############################################################################
	message("\r\nINSTALLATION ASSIMP----------------------------------------------\r\n")
	execute_process(COMMAND ${BIN_BREW} install assimp
				WORKING_DIRECTORY "${PROJECT_DIR}/")
	find_package(ASSIMP REQUIRED)
	link_directories(
		"${ASSIMP_DIR}/../../../lib"
		)
	include_directories(${ASSIMP_INCLUDE_DIR})
	message("${ASSIMP_INCLUDE_DIR}")
	message("${ASSIMP_DIR}/../../../lib")
	#SOIL
	############################################################################
	message("\r\nINSTALLATION SOIL------------------------------------------------\r\n")
	if(NOT EXISTS "${PROJECT_DIR}/SOIL")
		execute_process(COMMAND git clone "https://github.com/alelievr/SOIL2.git" "SOIL"
						WORKING_DIRECTORY ${PROJECT_DIR}/
						)
		if(NOT EXISTS "${PROJECT_DIR}/SOIL/lib")
			execute_process(COMMAND make
						WORKING_DIRECTORY ${PROJECT_DIR}/SOIL
						)
		endif()
	else()
		message("Warning: SOIL 2 is already installed")
	endif()
	link_directories(${PROJECT_DIR}/SOIL)
	include_directories(${PROJECT_DIR}/SOIL/incs)
	message("${PROJECT_DIR}/SOIL/incs")
	message("${PROJECT_DIR}/SOIL")
	message("\r\nINSTALLATION NETWORK --------------------------------------------\r\n")
	#if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../network/libnetwork.a")
		execute_process(COMMAND make
					WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../network/
					)
	#else()
		#message("Warning: libnetwork.a is already installed")
	#endif()
		link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../network/)
		include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../network/includes/)
	message("")
endif()

if (WIN32)
	# TODO windows
endif()

if (UNIX AND NOT APPLE)
	# TODO linux
endif()

################################################################################
# Build executables
################################################################################

file(GLOB_RECURSE CLIENT_SRC srcs/*.cpp)

add_executable(${PROJECT_NAME} ${CLIENT_SRC})

include_directories(${PROJECT_NAME} includes)

target_link_libraries(${PROJECT_NAME} SDL2 sdl2_ttf sdl2_image glm assimp SOIL2 network ${OPENGL_gl_LIBRARY} ${OPENAL_LIBRARY})
