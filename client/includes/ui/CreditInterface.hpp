#ifndef CREDITINTERFACE_HPP
# define CREDITINTERFACE_HPP

# include "Bomberman.hpp"

class CreditInterface : public UIInterface
{
	public:

		CreditInterface( void );
		CreditInterface( CreditInterface const & src );
		virtual ~CreditInterface( void );

		CreditInterface &					operator=( CreditInterface const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, CreditInterface const & i);

		void								draw(void);

	private:
		Canvas								*canvas;

};

#endif
