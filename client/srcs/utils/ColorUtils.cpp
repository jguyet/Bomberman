#include "Bomberman.hpp"

// STATIC ########################################################

void						ColorUtils::hexaColorToRGB( glm::vec3 &rgb, const char *hexcolor )
{
	// int r, g, b;
    //
	// if (hexcolor[0] == "#")
	// 	hexcolor++;
	// sscanf(hexcolor, "%02x%02x%02x", &r, &g, &b);
	// rgb.x = r;
	// rgb.y = g;
	// rgb.z = b;
}

void						ColorUtils::hexaColorToRGB( glm::vec3 &rgb, std::string hexcolor )
{
	int r, g, b;

	if (hexcolor.substr(0, 1) == "#")
		hexcolor.erase(0,1);
	sscanf(hexcolor.c_str(), "%02x%02x%02x", &r, &g, &b);
	rgb.x = r;
	rgb.y = g;
	rgb.z = b;
}

// ###############################################################

// CANONICAL #####################################################

ColorUtils::ColorUtils ( void )
{
	return ;
}

ColorUtils::ColorUtils ( ColorUtils const & src )
{
	*this = src;
	return ;
}

ColorUtils &				ColorUtils::operator=( ColorUtils const & rhs ) {
	if (this != &rhs) {
		// make stuff
	}
	return (*this);
}

ColorUtils::~ColorUtils ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, ColorUtils const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

// ###############################################################
