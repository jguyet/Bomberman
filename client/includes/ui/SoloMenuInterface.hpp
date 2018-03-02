#ifndef SOLOMENUINTERFACE_HPP
# define SOLOMENUINTERFACE_HPP


# include "graphics/keys/KeyBoard.hpp"
# include "Bomberman.hpp"

class SoloMenuInterface : public UIInterface , public KeyBoardEventHandler
{
	public:

											SoloMenuInterface( void );
											SoloMenuInterface( SoloMenuInterface const & src );
		virtual								~SoloMenuInterface( void );

		SoloMenuInterface &					operator=( SoloMenuInterface const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, SoloMenuInterface const & i);

		void								handleUP(unsigned int key);

		void								draw(void);

		int									current_position;
	private:
		Canvas								*canvas;
};

#endif
