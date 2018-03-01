#ifndef ACTIONQUEUEMANAGER_HPP
# define ACTIONQUEUEMANAGER_HPP

#include "Bomberman.hpp"
#include <mutex>
#include <atomic>

class ActionQueue;
class ActionQueueManager
{
	public:

		static ActionQueueManager		*Instance();

		ActionQueueManager();
		ActionQueueManager( ActionQueueManager const & src );
		virtual ~ActionQueueManager();
		void	addAction(ActionQueue *action);
		void	removeAction(ActionQueue *action);
		void	consume();
		void	doAction(ActionQueue *action);
		void	removeAllActions(void);
		ActionQueueManager &							operator=( ActionQueueManager const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, ActionQueueManager const & i);
		std::vector<ActionQueue*>			actions;

		static std::atomic<ActionQueueManager*>	pInstance;
		static std::mutex						mutex;
};

#endif
