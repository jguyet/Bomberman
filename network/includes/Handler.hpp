#ifndef HANDLER_HPP
# define HANDLER_HPP

# include "All.hpp"
# include "IMessage.hpp"
# include <stdarg.h>
# include <map>

class Handler
{
	public:

		Handler(SOCK socket, ...);
		Handler( Handler const & src );
		virtual ~Handler();

		void handleMessage(IMessage *message);
		Handler &							operator=( Handler const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Handler const & i);
		std::map<int, void*> handlers;
		SOCK socket;
};

#endif
