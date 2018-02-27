#ifndef GAMESTARTEDMESSAGE_HPP
# define GAMESTARTEDMESSAGE_HPP

#include "All.hpp"
#include "IMessage.hpp"

class GameStartedMessage : public IMessage
{
	public:
		static constexpr int ID = 8;
		GameStartedMessage(bool started);
		GameStartedMessage( GameStartedMessage const & src );
		virtual ~GameStartedMessage();

		GameStartedMessage &							operator=( GameStartedMessage const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, GameStartedMessage const & i);
		bool started;
};

#endif
