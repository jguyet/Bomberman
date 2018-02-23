#ifndef ACTIONMESSAGE_HPP
# define ACTIONMESSAGE_HPP

#include "All.hpp"
#include "IMessage.hpp"
#include "objs/ActionObject.hpp"

class ActionMessage : public IMessage
{
	public:
		static constexpr int ID = 6;

		ActionMessage(ActionObject&, int);
		ActionMessage( ActionMessage const & src );
		virtual ~ActionMessage();

		ActionMessage &							operator=( ActionMessage const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, ActionMessage const & i);

		ActionObject	action;
		int				byPlayer;
};

#endif
