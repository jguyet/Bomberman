#include "managers/ActionQueueManager.hpp"
#include "models/ActionQueue.hpp"
#include "messages/MapSelectMessage.hpp"

ActionQueueManager*			ActionQueueManager::instance = new ActionQueueManager();

ActionQueueManager::ActionQueueManager ()
{
}

ActionQueueManager::ActionQueueManager ( ActionQueueManager const & src )
{
	*this = src;
}

ActionQueueManager &				ActionQueueManager::operator=( ActionQueueManager const & rhs )
{
	return (*this);
}

ActionQueueManager::~ActionQueueManager ()
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, ActionQueueManager const & i)
{
	return (o);
}

void ActionQueueManager::addAction(ActionQueue *action)
{
	this->actions.push_back(action);
}

void	ActionQueueManager::removeAction(ActionQueue *action)
{
	for (int i = 0; i < this->actions.size(); i++)
	{
		if (this->actions[i] == action) {
			this->actions.erase(this->actions.begin() + i);
			delete action;
			break;
		}
	}
}

void ActionQueueManager::doAction(ActionQueue *action)
{
	switch (action->messageId)
	{
		case MapSelectMessage::ID:
			MapSelectMessage	*mapMessage = (MapSelectMessage*)action->message;
			BombermanClient::instance->current_scene = new GameScene(mapMessage->name);
		break;
	}
}

void ActionQueueManager::consume()
{
	if (this->actions.size() > 0) {
		mutex.lock();
		this->doAction(this->actions[0]);
		this->removeAction(this->actions[0]);
		mutex.unlock();
	}
}
