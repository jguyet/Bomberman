#ifndef SAVEMANAGER_HPP
# define SAVEMANAGER_HPP

#include "Bomberman.hpp"

class SaveManager
{
	public:

		SaveManager(GameScene*);
		SaveManager( SaveManager const & src );
		virtual ~SaveManager();

		SaveManager &							operator=( SaveManager const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, SaveManager const & i);
	private:
		GameScene *scene;
};

#endif
