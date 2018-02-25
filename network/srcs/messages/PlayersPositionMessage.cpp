#include "messages/PlayersPositionMessage.hpp"

PlayersPositionMessage::PlayersPositionMessage (std::vector<PlayerPositionObject> pos) : IMessage(PlayersPositionMessage::ID, sizeof(IMessage) + sizeof(PlayersPositionMessage))
{
	for (int i = 0; i < pos.size(); i++) {
		this->positions[i] = pos[i];
	}
	this->positions_length = pos.size();
}

PlayersPositionMessage::PlayersPositionMessage ( PlayersPositionMessage const & src )
{
	*this = src;
}

PlayersPositionMessage &				PlayersPositionMessage::operator=( PlayersPositionMessage const & rhs )
{
	return (*this);
}

PlayersPositionMessage::~PlayersPositionMessage ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, PlayersPositionMessage const & i)
{

	return (o);
}
