#include "messages/MapSelectMessage.hpp"

MapSelectMessage::MapSelectMessage (std::string map_name) : IMessage(MapSelectMessage::ID, sizeof(IMessage) + sizeof(MapSelectMessage))
{
	this->name = map_name;
}

MapSelectMessage::MapSelectMessage ( MapSelectMessage const & src )
{
	*this = src;
}

MapSelectMessage &				MapSelectMessage::operator=( MapSelectMessage const & rhs )
{
	return (*this);
}

MapSelectMessage::~MapSelectMessage ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, MapSelectMessage const & i)
{

	return (o);
}
