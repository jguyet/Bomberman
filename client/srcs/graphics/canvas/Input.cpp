#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Input::Input ( void )
{
	KeyBoard::instance->addHandler("Input", this);
	return ;
}

Input::Input ( Input const & src )
{
	*this = src;
	return ;
}

Input &				Input::operator=( Input const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Input::~Input ( void )
{
	KeyBoard::instance->removeHandler("Input");
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Input const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Input::handleUP(unsigned int key)
{
	std::cout << "Up      Key(" << key << ")" << std::endl;
}

void						Input::handleDOWN(unsigned int key)
{
	std::cout << "Down    Key(" << key << ")" << std::endl;
}

void						Input::handleRELEASE(unsigned int key)
{
	std::cout << "Release Key(" << key << ")" << std::endl;
}

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
