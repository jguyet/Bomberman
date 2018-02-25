#ifndef COLORUTILS_HPP
# define COLORUTILS_HPP

# include "Bomberman.hpp"

class ColorUtils
{
	public:
		// STATICS #############################################################
		static void							hexaColorToRGB( glm::vec3 &rgb, const char *hexcolor );
		static void							hexaColorToRGB( glm::vec3 &rgb, std::string hexcolor );
		// #####################################################################
		// CANONICAL ###########################################################
											ColorUtils( void );
											ColorUtils( ColorUtils const & src );
		virtual								~ColorUtils( void );

		ColorUtils &						operator=( ColorUtils const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, ColorUtils const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		// #####################################################################
	private:
		// PRIVATE #############################################################
		// #####################################################################
};

#endif
