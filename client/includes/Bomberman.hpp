/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bomberman.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 09:43:10 by jguyet            #+#    #+#             */
/*   Updated: 2018/03/03 04:26:46 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BOMBERMAN_HPP
# define BOMBERMAN_HPP

# if __APPLE__
#  define GLFW_INCLUDE_GLCOREARB
# endif

# ifdef linux
#   include <GL/glew.h>
#   include <SDL2/SDL.h>
#   include <SDL2/SDL_image.h>
#   include <SDL2/SDL_ttf.h>
#   include <SDL2/SDL_mixer.h>
# endif
# ifdef __APPLE__
#   include <OpenGL/gl3.h>
#   include <SDL2/SDL.h>
#   include <SDL2/SDL_image.h>
#   include <SDL2/SDL_ttf.h>
#   include <SDL2/SDL_mixer.h>
# endif

#include <OpenAL/OpenAL.h>

# include <SOIL2.h>
# include <glm/glm.hpp>
# include <glm/vec3.hpp> // glm::vec3
# include <glm/vec4.hpp> // glm::vec4
# include <glm/mat4x4.hpp> // glm::mat4
# include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
# include <glm/gtc/quaternion.hpp>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <iostream> //std::
# include <vector>
# include <list>
# include <sstream>
# include <fstream>
# include <map>
# include <set>
# include <functional>
# include <algorithm>

# include <assimp/Importer.hpp>      // C++ importer interface
# include <assimp/scene.h>           // Output data structure
# include <assimp/postprocess.h>     // Post processing flags

# define RELEASE GLFW_RELEASE
# define PRESS GLFW_PRESS
# define REPEAT GLFW_REPEAT

# define SPEED 0.07f
# define BOMB_TIME 5000L

/*
** Utils Methodes
*/
std::vector<std::string>		split(const std::string &s, char delim);
std::vector<std::string>		split_string(const std::string &s, const std::string &delim);
std::vector<std::string> 		split_string_without(const std::string &s, const std::string &delim, const std::string &without);
void							file_get_contents(std::string &content, std::string const &file_path);
std::string						trim(std::string const &s);
void							replaceAll(std::string& source, const std::string& from, const std::string& to);

# include "network/Socket.hpp"

/*
** Static Classes
*/
# include "utils/TimeUtils.hpp"
# include "utils/ShaderUtils.hpp"
# include "utils/ColorUtils.hpp"
# include "utils/CSSInterpretor.hpp"
# include "utils/Properties.hpp"

// GRAPHICS ####################################################################
/*
** OBJECTS
*/
# include "graphics/components/Component.hpp"
# include "graphics/Camera.hpp"
# include "graphics/GameObject.hpp"
# include "graphics/canvas/Canvas.hpp"
/*
** UI Module
*/
# include "graphics/UIInterface.hpp"
/*
** Components
*/
# include "graphics/components/Model.hpp"
# include "graphics/components/BoxCollider.hpp"
# include "graphics/components/Script.hpp"
# include "graphics/components/Animator.hpp"

# include "graphics/Scene.hpp"
// #############################################################################

/*
**	Managers
*/
# include "managers/MapManager.hpp"
# include "managers/SaveManager.hpp"

/*
** Scenes
*/
# include "scenes/GameScene.hpp"
# include "scenes/MainMenuScene.hpp"
# include "scenes/SoloMenuScene.hpp"
# include "scenes/SettingScene.hpp"

/*
** Others
*/
# include "graphics/keys/KeyBoard.hpp"
# include "graphics/keys/Mouse.hpp"
# include "graphics/loop/IRenderLoop.hpp"
# include "graphics/loop/RenderLoop.hpp"


/*
** Main_Client
*/
# include "client/BombermanClient.hpp"
# include "client/Loader.hpp"
# include "Factory.hpp"

/*
** AI
*/
# include "AI/Module_h.hpp"
# include "AI/A_star.hpp"
# include "AI/AI.hpp"

# include "scripts/GameScene/BotControllerScript.hpp"
// # include "scripts/GameScene/CharacterControllerScript.hpp"

#endif
