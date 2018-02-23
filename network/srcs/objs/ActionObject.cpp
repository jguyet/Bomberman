#include "objs/ActionObject.hpp"

ActionObject::ActionObject()
{

}

ActionObject::ActionObject(ActionType& type, float x, float y, float z)
{
	this->type = type;
	this->x = x;
	this->y = y;
	this->z = z;
}

ActionObject::ActionObject ( ActionObject const & src )
{
	*this = src;
}

ActionObject &				ActionObject::operator=( ActionObject const & rhs )
{
	this->type = rhs.type;
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return (*this);
}

ActionObject::~ActionObject ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, ActionObject const & i)
{
	return (o);
}
