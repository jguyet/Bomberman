#ifndef SCRIPT_HPP
# define SCRIPT_HPP

# include "Bomberman.hpp"

class Script : public Component
{
	public:

		Script( void );
		Script( Script const & src );
		virtual ~Script( void );

		Script &							operator=( Script const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Script const & i);

		virtual void						Update(void) = 0;

		bool								collide = false;
		std::vector<GameObject*>			colliders;
};

#endif
