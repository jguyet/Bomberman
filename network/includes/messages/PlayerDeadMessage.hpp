#ifndef PLAYERDEADMESSAGE_HPP
# define PLAYERDEADMESSAGE_HPP

#include "All.hpp"
#include "IMessage.hpp"

class PlayerDeadMessage : public IMessage
{
	public:
		static constexpr int ID = 7;

		PlayerDeadMessage(int playerId);
		PlayerDeadMessage( PlayerDeadMessage const & src );
		virtual ~PlayerDeadMessage();

		PlayerDeadMessage &							operator=( PlayerDeadMessage const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, PlayerDeadMessage const & i);

		int playerId;
};

#endif
