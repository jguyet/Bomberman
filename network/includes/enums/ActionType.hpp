#ifndef ACTION_TYPE_HPP
# define ACTION_TYPE_HPP

enum class ActionType : unsigned char
{
	TYPE_NONE = 0,
	TYPE_BOMB = 1,
	TYPE_BONUS_SPEED_UP = 2,
	TYPE_BONUS_BOMB_UP = 3,
	TYPE_BONUS_POWER_UP = 4,
};

#endif
