#ifndef TIMEUTILS_HPP
# define TIMEUTILS_HPP

# include "Bomberman.hpp"

# include <chrono>

class TimeUtils
{
	public:
		// STATICS #############################################################
		static long							getCurrentNanoSeconds( void );
		// #####################################################################
		// CANONICAL ###########################################################
											TimeUtils( void );
											TimeUtils( TimeUtils const & src );
		virtual								~TimeUtils( void );

		TimeUtils &							operator=( TimeUtils const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, TimeUtils const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		// #####################################################################
	private:
		// PRIVATE #############################################################
		// #####################################################################
};

#endif
