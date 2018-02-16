#ifndef CASE_HPP
# define CASE_HPP

#include "Bomberman.hpp"

/*
**	Entity
*/
struct Case {
	GameObject		*ground;
	GameObject		*obstacle;
	bool			walkable;
	glm::vec3		position;
};

#endif
