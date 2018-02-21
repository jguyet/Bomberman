#ifndef PROCESSOR_HPP
# define PROCESSOR_HPP

#include "All.hpp"
#include "Handler.hpp"

#include "messages/PlayerPositionMessage.hpp"
class Processor
{
	public:
		Processor();
		Processor( Processor const & src );
		virtual ~Processor();

		Processor &							operator=( Processor const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Processor const & i);
		static void			PlayerPositionMessageHandler(SOCK, PlayerPositionMessage*);
		static int			*getMessageId(int id);
};

#endif
