#ifndef NEWPLAYERMESSAGE_HPP
# define NEWPLAYERMESSAGE_HPP

#include "All.hpp"
#include "IMessage.hpp"
#include "objs/PlayerPositionObject.hpp"

class NewPlayerMessage : public IMessage
{
	public:
		static constexpr int ID = 4;
		NewPlayerMessage(PlayerPositionObject&, bool);
		NewPlayerMessage( NewPlayerMessage const & src );
		virtual ~NewPlayerMessage();

		NewPlayerMessage &							operator=( NewPlayerMessage const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, NewPlayerMessage const & i);
		PlayerPositionObject	position;
		bool					owner;
};

#endif
