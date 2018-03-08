#ifndef ENDOFGAMEMESSAGE_HPP
# define ENDOFGAMEMESSAGE_HPP

#include "All.hpp"
#include "IMessage.hpp"

class EndOfGameMessage : public IMessage
{
	public:
		static constexpr int ID = 9;
		EndOfGameMessage(bool is_winner);
		EndOfGameMessage( EndOfGameMessage const & src );
		virtual ~EndOfGameMessage();

		EndOfGameMessage &							operator=( EndOfGameMessage const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, EndOfGameMessage const & i);

		bool is_winner;
};

#endif
