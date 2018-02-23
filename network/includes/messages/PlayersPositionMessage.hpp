#ifndef PLAYERSPOSITIONMESSAGE_HPP
# define PLAYERSPOSITIONMESSAGE_HPP

#include "All.hpp"
#include "IMessage.hpp"
#include "objs/PlayerPositionObject.hpp"

#define MAX_POS 512

class PlayersPositionMessage : public IMessage
{
	public:
		static constexpr int ID = 5;

		PlayersPositionMessage(std::vector<PlayerPositionObject>);
		PlayersPositionMessage( PlayersPositionMessage const & src );
		virtual ~PlayersPositionMessage();

		PlayersPositionMessage &							operator=( PlayersPositionMessage const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, PlayersPositionMessage const & i);
		PlayerPositionObject				positions[MAX_POS];
		unsigned long						positions_length;
};

#endif
