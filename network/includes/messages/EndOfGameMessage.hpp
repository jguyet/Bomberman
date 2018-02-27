#ifndef ENDOFGAMEMESSAGE_HPP
# define ENDOFGAMEMESSAGE_HPP

#include "All.hpp"
#include "IMessage.hpp"

class EndOfGameMessage : public IMessage
{
	public:
		static constexpr int ID = 9;
		EndOfGameMessage();
		EndOfGameMessage( EndOfGameMessage const & src );
		virtual ~EndOfGameMessage();

		EndOfGameMessage &							operator=( EndOfGameMessage const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, EndOfGameMessage const & i);
};

#endif
