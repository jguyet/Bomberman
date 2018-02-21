#ifndef PROCESSOR_HPP
# define PROCESSOR_HPP

#include "All.hpp"
#include "Handler.hpp"

#include "messages/PlayerPositionMessage.hpp"
#include "messages/NewPlayerMessage.hpp"
#include "Managers/DataManager.hpp"
class Processor
{
	public:
		Processor();
		Processor( Processor const & src );
		virtual ~Processor();

		Processor &							operator=( Processor const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Processor const & i);
		static void			PlayerPositionMessageHandler(SOCK, PlayerPositionMessage*);
		static void			NewPlayerMessageHandler(SOCK, NewPlayerMessage*);
		static int			*getMessageId(int id);
};

#endif
