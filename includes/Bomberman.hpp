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

# include <glfw3.h>
# include <glm/vec3.hpp> // glm::vec3
# include <glm/vec4.hpp> // glm::vec4
# include <glm/mat4x4.hpp> // glm::mat4
# include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <iostream> //std::

# define RELEASE GLFW_RELEASE
# define PRESS GLFW_PRESS
# define REPEAT GLFW_REPEAT

/*
** Interfaces
*/
# include "graphics/IRenderLoop.hpp"
# include "controllers/IController.hpp"

/*
** Static Classes
*/
# include "utils/TimeUtils.hpp"

/*
** Classes
*/
# include "graphics/RenderLoop.hpp"
# include "graphics/keys/Keyboard.hpp"
# include "graphics/keys/Mouse.hpp"
# include "client/BombermanClient.hpp"

long			getCurrentNanoSeconds( void );

#endif
