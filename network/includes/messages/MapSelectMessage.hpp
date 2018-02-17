#ifndef MAPSELECTMESSAGE_HPP
# define MAPSELECTMESSAGE_HPP

#include "All.hpp"
#include "IMessage.hpp"

class MapSelectMessage : public IMessage
{
	public:
		static constexpr int ID = 2;

		MapSelectMessage(std::string map_name);
		MapSelectMessage( MapSelectMessage const & src );
		virtual ~MapSelectMessage();

		MapSelectMessage &							operator=( MapSelectMessage const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, MapSelectMessage const & i);
		std::string name;
};

#endif
