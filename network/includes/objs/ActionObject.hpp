#ifndef ACTIONOBJECT_HPP
# define ACTIONOBJECT_HPP

#include "All.hpp"
#include "enums/ActionType.hpp"

class ActionObject
{
	public:
		ActionObject();
		ActionObject(ActionType& type, float x, float y, float z);
		ActionObject( ActionObject const & src );
		virtual ~ActionObject();

		ActionObject &							operator=( ActionObject const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, ActionObject const & i);

		ActionType	type;
		float		x;
		float		y;
		float		z;
};

#endif
