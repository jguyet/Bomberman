#ifndef CSSINTERPRETOR_HPP
# define CSSINTERPRETOR_HPP

# include "graphics/components/Component.hpp"
# include "graphics/GameObject.hpp"
# include "graphics/canvas/Canvas.hpp"
# include "Bomberman.hpp"

class CSSInterpretor
{
	public:
		// STATICS #############################################################
		static void							interpretCSS( Tag *tag, const char *style );
		// #####################################################################
		// CANONICAL ###########################################################
											CSSInterpretor( void );
											CSSInterpretor( CSSInterpretor const & src );
		virtual								~CSSInterpretor( void );

		CSSInterpretor &					operator=( CSSInterpretor const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, CSSInterpretor const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		// #####################################################################
	private:
		// PRIVATE #############################################################
		// #####################################################################
};

#endif
