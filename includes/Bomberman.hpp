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

# include <SOIL2.h>
# include <glfw3.h>
# include <glm/vec3.hpp> // glm::vec3
# include <glm/vec4.hpp> // glm::vec4
# include <glm/mat4x4.hpp> // glm::mat4
# include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <iostream> //std::
# include <vector>
# include <list>
# include <sstream>
# include <fstream>
# include <map>

# define RELEASE GLFW_RELEASE
# define PRESS GLFW_PRESS
# define REPEAT GLFW_REPEAT

std::vector<std::string>		split(const std::string &s, char delim);

/*
** Interfaces
*/
# include "graphics/IRenderLoop.hpp"
# include "controllers/IController.hpp"
# include "views/IView.hpp"

/*
** Static Classes
*/
# include "utils/TimeUtils.hpp"
# include "utils/ShaderUtils.hpp"

/*
** Classes
*/
# include "graphics/components/Camera.hpp"
# include "graphics/components/Transform.hpp"

/*
** Micro controllers
*/
# include "views/simple/SimpleView.hpp"

# include "graphics/RenderLoop.hpp"
# include "graphics/keys/KeyBoard.hpp"
# include "graphics/keys/Mouse.hpp"
# include "client/BombermanClient.hpp"

#endif
