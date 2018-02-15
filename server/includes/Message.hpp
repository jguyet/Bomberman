#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include "All.hpp"
#include "IMessage.hpp"

class Message : public IMessage
{
	public:

		Message();
		Message( Message const & src );
		virtual ~Message();

		Message &							operator=( Message const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Message const & i);
	private:
		int Interessant;
		std::string salope;
};

#endif
