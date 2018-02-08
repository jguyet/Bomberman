#include "Bomberman.hpp"

// STATIC ########################################################

long						GameObject::uid = 0;
std::map<long, GameObject*>	GameObject::objects = std::map<long, GameObject*>();

bool	checkCollision(GameObject *a1, GameObject *b, BoxCollider *a)
{
   //check the X axis
   if(abs((a1->transform.position.x + a->center.x) - b->transform.position.x) < a->size.x + b->transform.scale.x)
   {
      //check the Y axis
      if(abs((a1->transform.position.y + a->center.y) - b->transform.position.y) < a->size.y + b->transform.scale.y)
      {
          //check the Z axis
          if(abs((a1->transform.position.z + a->center.z) - b->transform.position.z) < a->size.z + b->transform.scale.z)
          {
             return true;
          }
      }
   }
   return false;
}

void						GameObject::ProcessPhisicsComponents(void)
{
	for (std::map<long, GameObject*>::iterator it = GameObject::objects.begin(); it != GameObject::objects.end(); it++)
	{
		if (it->second->GetComponent<BoxCollider>() == NULL)
			continue ;
		for (std::map<long, GameObject*>::iterator it2 = GameObject::objects.begin(); it2 != GameObject::objects.end(); it2++)
		{
			if (it->second->id == it2->second->id)
				continue ;
			if (checkCollision(it->second, it2->second, it->second->GetComponent<BoxCollider>())) {
				it->second->GetComponent<BoxCollider>()->m(it->second, it2->second);
				break ;
			}
		}
	}
}

// ###############################################################

// CANONICAL #####################################################

GameObject::GameObject ( void )
{
	this->transform.position = glm::vec3(0,0,0);
	this->transform.rotation = glm::vec3(0,0,0);
	this->transform.scale = glm::vec3(1,1,1);
	this->tag = "Default";
	GameObject::uid += 1;
	this->id = GameObject::uid;
	GameObject::objects[this->id] = this;
	return ;
}

GameObject::GameObject ( GameObject const & src )
{
	*this = src;
	return ;
}

GameObject &				GameObject::operator=( GameObject const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GameObject::~GameObject ( void )
{
	GameObject::objects.erase(this->id);
	return ;
}

std::ostream &				operator<<(std::ostream & o, GameObject const & i)
{
	o << "GameObject :" << std::endl;
	o << "position : vec3(" << i.transform.position.x << "," << i.transform.position.y << "," << i.transform.position.z << ")" << std::endl;
	o << "rotation : vec3(" << i.transform.rotation.x << "," << i.transform.rotation.y << "," << i.transform.rotation.z << ")" << std::endl;
	o << "scale : vec3(" << i.transform.scale.x << "," << i.transform.scale.y << "," << i.transform.scale.z << ")" << std::endl;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						GameObject::Translate(glm::vec3 v)
{
	this->transform.position = this->transform.position + v;
}

void						GameObject::ProcessRenderingComponents(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix)
{
	if (this->GetComponent<Model>() != NULL) {
		this->GetComponent<Model>()->draw(this->transform.position, this->transform.rotation, this->transform.scale, projectionMatrix, viewMatrix);
	}
}

// ###############################################################
