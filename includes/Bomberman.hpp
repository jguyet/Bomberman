/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bomberman.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 09:43:10 by jguyet            #+#    #+#             */
/*   Updated: 2018/01/31 09:43:11 by jguyet           ###   ########.fr       */
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
#   include <SDL2/SDL_mixer.h>
#   include <SDL2/SDL_ttf.h>
# endif
# ifdef __APPLE__
#   include <OpenGL/gl3.h>
#   include <SDL2/SDL.h>
#   include <SDL2/SDL_image.h>
#   include <SDL2/SDL_mixer.h>
#   include <SDL2/SDL_ttf.h>
# endif

# include <SOIL2.h>
# include <glm/glm.hpp>
# include <glm/vec3.hpp> // glm::vec3
# include <glm/vec4.hpp> // glm::vec4
# include <glm/mat4x4.hpp> // glm::mat4
# include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
# include <glm/gtc/quaternion.hpp>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <iostream> //std::
# include <vector>
# include <list>
# include <sstream>
# include <fstream>
# include <map>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

# define RELEASE GLFW_RELEASE
# define PRESS GLFW_PRESS
# define REPEAT GLFW_REPEAT

/*
** Utils Methodes
*/
std::vector<std::string>		split(const std::string &s, char delim);

/*
** Static Classes
*/
# include "utils/TimeUtils.hpp"
# include "utils/ShaderUtils.hpp"

/*
** Components
*/
# include "graphics/components/Component.hpp"
# include "graphics/components/Camera.hpp"
# include "graphics/components/Model.hpp"
# include "graphics/components/BoxCollider.hpp"
# include "graphics/components/GameObject.hpp"
/*
** Canvas :
*/
# include "graphics/canvas/Text.hpp"
# include "graphics/canvas/Image.hpp"
# include "graphics/canvas/Canvas.hpp"

/*
** Interfaces
*/
# include "graphics/IRenderLoop.hpp"


/*
** Models
*/
# include "models/IModel.hpp"
# include "models/Map.hpp"

/*
** Controllers
*/
# include "controllers/IController.hpp"
# include "controllers/GameController.hpp"

/*
** Others
*/
# include "graphics/keys/KeyBoard.hpp"
# include "graphics/keys/Mouse.hpp"
# include "graphics/IRenderLoop.hpp"
# include "graphics/RenderLoop.hpp"

/*
** Main_Client
*/
# include "client/BombermanClient.hpp"
# include "Factory.hpp"

#endif
