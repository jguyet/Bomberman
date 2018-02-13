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
	message("MACOS ------------------------------------------------------------o")
	set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/macos")

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
	message("INSTALLATION SDL-------------------------------------------------")
	execute_process(COMMAND ${BIN_BREW} install sdl2
							WORKING_DIRECTORY "${PROJECT_DIR}/")
	find_package(SDL2 REQUIRED)
	message("-----------------------------------------------------------------")
	link_directories("${SDL2_DIR}/../../../lib")
	include_directories(${SDL2_INCLUDE_DIR})


	# sdl2_mixer sdl2_mixer sdl2_image
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

	execute_process(COMMAND ${BIN_BREW} install sdl2_mixer
				WORKING_DIRECTORY "${PROJECT_DIR}/")
	find_path(SDL2_MIXER_INCLUDE_DIR SDL2/SDL_mixer.h
				  HINTS
				    ENV HOME
				    ${SDL2_DIR}
					${BREW_DIR}
				  PATH_SUFFIXES SDL2
	                # path suffixes
	                include/SDL2 include)
	message(${SDL2_MIXER_INCLUDE_DIR})
	include_directories(${SDL2_MIXER_INCLUDE_DIR})
	find_path(SDL2_MIXER_LIB_DIR libSDL2_mixer.a HINTS ${BREW_DIR}/../lib)
	message("${SDL2_MIXER_LIB_DIR}")
	link_directories("${SDL2_MIXER_LIB_DIR}")

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
	message("INSTALLATION GLM-------------------------------------------------")
	execute_process(COMMAND ${BIN_BREW} install glm
				WORKING_DIRECTORY "${PROJECT_DIR}/")
	find_package(GLM REQUIRED)
	message("-----------------------------------------------------------------")
	link_directories("${GLM_DIR}/../../../lib")
	find_path(GLM_INCLUDE_DIR glm/glm.hpp
				  HINTS
				    ENV HOME
				    ${GLM_DIR}
					${BREW_DIR}
				  PATH_SUFFIXES glm
	                # path suffixes
	                include/glm include)
	message(${GLM_INCLUDE_DIR})
	include_directories("${GLM_INCLUDE_DIR}")
	#ASSIMP
	############################################################################
	message("INSTALLATION ASSIMP----------------------------------------------")
	execute_process(COMMAND ${BIN_BREW} install assimp
				WORKING_DIRECTORY "${PROJECT_DIR}/")
	find_package(ASSIMP REQUIRED)
	message("-----------------------------------------------------------------")
	link_directories(
		"${ASSIMP_DIR}/../../../lib"
		)
	include_directories("${GLM_INCLUDE_DIR}")
	#SOIL
	############################################################################
	message("INSTALLATION SOIL------------------------------------------------")
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
		link_directories(
		  ${PROJECT_DIR}/SOIL
		)
		include_directories(
			${PROJECT_DIR}/SOIL/incs/SOIL
			${PROJECT_DIR}/SOIL/incs
			${PROJECT_DIR}/SOIL
		)
	message("-----------------------------------------------------------------")
	message("------------------------------------------------------------------o")
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
target_link_libraries(${PROJECT_NAME} SDL2 sdl2_ttf sdl2_image glm assimp SOIL2 ${OPENGL_gl_LIBRARY} ${OPENAL_LIBRARY})

#target_link_libraries(${PROJECT_NAME} "sdl2-config --libs SDL2_image SDL2_mixer SDL2_ttf")
