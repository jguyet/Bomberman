#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

DoorControllerScript::DoorControllerScript ()
{
	return ;
}

DoorControllerScript::DoorControllerScript ( DoorControllerScript const & src )
{
	*this = src;
	return ;
}

DoorControllerScript &				DoorControllerScript::operator=( DoorControllerScript const & rhs )
{
	return (*this);
}

DoorControllerScript::~DoorControllerScript ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, DoorControllerScript const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						DoorControllerScript::Start(void)
{
}

void						DoorControllerScript::Update(void)
{

}

// ###############################################################
