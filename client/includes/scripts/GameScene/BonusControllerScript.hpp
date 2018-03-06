#ifndef BONUSCONTROLLERSCRIPT_HPP
# define BONUSCONTROLLERSCRIPT_HPP

# include "Bomberman.hpp"

class BonusControllerScript : public Script
{
	public:

		BonusControllerScript( void );
		BonusControllerScript( BonusControllerScript const & src );
		virtual ~BonusControllerScript( void );

		BonusControllerScript &							operator=( BonusControllerScript const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, BonusControllerScript const & i);

		void								Update(void);
};

#endif
