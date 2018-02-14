#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Script::Script ( void )
{
	return ;
}

Script::Script ( Script const & src )
{
	*this = src;
	return ;
}

Script &				Script::operator=( Script const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Script::~Script ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Script const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Script::Start(void)
{

}

void						Script::Update(void)
{

}

void						Script::OnPreRender(void)
{

}

void						Script::OnEndRender(void)
{

}

void						Script::OnCollisionEnter(GameObject *collider)
{

}

// ###############################################################
