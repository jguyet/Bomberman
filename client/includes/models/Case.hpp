#ifndef CASE_HPP
# define CASE_HPP

#include "Bomberman.hpp"

/*
**	Entity
*/
struct Case {
	GameObject		*ground;
	GameObject		*obstacle;
	GameObject		*door;
	GameObject		*environement;

	bool			walkable;
	glm::vec3		position;
};

#endif
