#include "Bomberman.hpp"

// STATIC ########################################################
bool	checkCollision(GameObject *a1, GameObject *b, BoxCollider *a)
{
   //check the X axis
   if(abs((a1->transform.position.x + a->center.x) - b->transform.position.x) < a->size.x + 1.f)//b->transform.scale.x)
   {
      //check the Y axis
      if(abs((a1->transform.position.y + a->center.y) - b->transform.position.y) < a->size.y + 1.f)//b->transform.scale.y)
      {
          //check the Z axis
          if(abs((a1->transform.position.z + a->center.z) - b->transform.position.z) < a->size.z + 1.f)//b->transform.scale.z)
          {
             return true;
          }
      }
   }
   return false;
}

void						BoxCollider::Check3DCollisions(std::unordered_map<long, GameObject*> const &gameObjects)
{
	for (auto const &it : gameObjects)
	{
		if (it.second->toDelete)
			continue ;
		bool collide = false;
		Script *script = it.second->GetComponent<Script>();
		BoxCollider *boxcollider = it.second->GetComponent<BoxCollider>();

		if (boxcollider == NULL)
			continue ;
		if (script == NULL)
			continue ;
		if (script->frame == 0L)
			continue ;
		for (auto const &it2 : gameObjects)
		{
			if (it2.second->toDelete)
				continue ;
			if (it.second->id == it2.second->id)
				continue ;
			if (checkCollision(it.second, it2.second, boxcollider)) {
				//TODO after collide
				script->OnCollisionEnter(it2.second);
			}
		}
	}
}
// ###############################################################

// CANONICAL #####################################################

BoxCollider::BoxCollider ( glm::vec3 center, glm::vec3 size  )
{
	this->center = center;
	this->size = size;
	return ;
}

BoxCollider::BoxCollider ( BoxCollider const & src )
{
	*this = src;
	return ;
}

BoxCollider &				BoxCollider::operator=( BoxCollider const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

BoxCollider::~BoxCollider ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, BoxCollider const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
