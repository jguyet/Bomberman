#ifndef LOADER_HPP
# define LOADER_HPP

#include "Bomberman.hpp"

class Loader
{
	public:

		Loader();
		Loader( Loader const & src );
		virtual ~Loader();

		void								loadShaders();
		void								loadModels();
		Loader &							operator=( Loader const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Loader const & i);
};

#endif
