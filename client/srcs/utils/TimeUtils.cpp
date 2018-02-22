#include "Bomberman.hpp"

// STATIC ########################################################

long					TimeUtils::getCurrentNanoSeconds( void )
{
	auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);

    auto value = now_ms.time_since_epoch();
    return (value.count());
}

long					TimeUtils::getCurrentSystemMillis( void )
{
    return (TimeUtils::getCurrentNanoSeconds() / 1000000L);
}

// ###############################################################

// CANONICAL #####################################################

TimeUtils::TimeUtils ( void )
{
	return ;
}

TimeUtils::TimeUtils ( TimeUtils const & src )
{
	*this = src;
	return ;
}

TimeUtils &				TimeUtils::operator=( TimeUtils const & rhs ) {
	if (this != &rhs) {
		// make stuff
	}
	return (*this);
}

TimeUtils::~TimeUtils ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, TimeUtils const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

// ###############################################################
