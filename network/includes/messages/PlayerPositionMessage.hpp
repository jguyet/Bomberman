#ifndef PLAYERPOSITIONMESSAGE_HPP
# define PLAYERPOSITIONMESSAGE_HPP

#include "All.hpp"
#include "IMessage.hpp"
#include "objs/PlayerPositionObject.hpp"

class PlayerPositionMessage : public IMessage
{
	public:
		static constexpr int ID = 3;

		PlayerPositionMessage(PlayerPositionObject &object);
		PlayerPositionMessage( PlayerPositionMessage const & src );
		virtual ~PlayerPositionMessage();

		PlayerPositionMessage &							operator=( PlayerPositionMessage const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, PlayerPositionMessage const & i);

		PlayerPositionObject playerPosition;
};

#endif
