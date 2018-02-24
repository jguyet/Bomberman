#include "Bomberman.hpp"

// STATIC ########################################################

void				CSSInterpretor::interpretCSS( Tag *tag )
{
	
}

// ###############################################################

// CANONICAL #####################################################

CSSInterpretor::CSSInterpretor ( void )
{
	return ;
}

CSSInterpretor::CSSInterpretor ( CSSInterpretor const & src )
{
	*this = src;
	return ;
}

CSSInterpretor &			CSSInterpretor::operator=( CSSInterpretor const & rhs ) {
	if (this != &rhs) {
		// make stuff
	}
	return (*this);
}

CSSInterpretor::~CSSInterpretor ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, CSSInterpretor const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

// ###############################################################
