#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

UIInterface::UIInterface ( const char *ui_file )
{
	this->initialize(ui_file);
	return ;
}

UIInterface::UIInterface ( UIInterface const & src )
{
	*this = src;
	return ;
}

UIInterface &				UIInterface::operator=( UIInterface const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

UIInterface::~UIInterface ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, UIInterface const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

Tag							*UIInterface::getElementById(const char *id)
{
	std::ostringstream os;

	os << id;
	if (this->elements.count(os.str()) == 0)
		return NULL;
	return (this->elements[os.str()]);
}

// ###############################################################

void						UIInterface::initialize( const char *ui_file )
{
	//TODO build elements
}
