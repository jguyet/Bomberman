#ifndef ACTIONQUEUEMANAGER_HPP
# define ACTIONQUEUEMANAGER_HPP

#include "Bomberman.hpp"
#include <mutex>

class ActionQueue;
class ActionQueueManager
{
	public:
		static ActionQueueManager					*instance;

		ActionQueueManager();
		ActionQueueManager( ActionQueueManager const & src );
		virtual ~ActionQueueManager();
		void	addAction(ActionQueue *action);
		void	removeAction(ActionQueue *action);
		void	consume();
		void	doAction(ActionQueue *action);

		ActionQueueManager &							operator=( ActionQueueManager const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, ActionQueueManager const & i);
		std::vector<ActionQueue*>			actions;
		std::mutex							mutex;
};

#endif
