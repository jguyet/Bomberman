#include "managers/ActionQueueManager.hpp"
#include "models/ActionQueue.hpp"
#include "messages/MapSelectMessage.hpp"
#include "messages/NewPlayerMessage.hpp"

std::atomic<ActionQueueManager*> ActionQueueManager::pInstance { nullptr };
std::mutex ActionQueueManager::mutex;

ActionQueueManager* ActionQueueManager::Instance()
{
  if(pInstance == nullptr)
  {
  	std::lock_guard<std::mutex> lock(mutex);
  	if(pInstance == nullptr) {
  		pInstance = new ActionQueueManager();
  	}
  }
  return pInstance;
}

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
	ActionQueueManager::mutex.lock();
	this->actions.push_back(action);
	mutex.unlock();
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
		case MapSelectMessage::ID: {
			MapSelectMessage	*mapMessage = (MapSelectMessage*)action->message;
			BombermanClient::instance->current_scene = new GameScene(mapMessage->name);
			BombermanClient::instance->sock->newPlayer(2, 1, 4); // set a position random by available cases
		}
		break;

		case NewPlayerMessage::ID: {
			NewPlayerMessage	*message = (NewPlayerMessage*)action->message;
			GameObject *playerObject = Factory::newPlayer(message->position.playerId);
			GameScene* scene = dynamic_cast<GameScene*>(BombermanClient::instance->current_scene);
			playerObject->transform.scale = glm::vec3(3,3,3);
			playerObject->transform.rotation = glm::vec3(0,0,0);
			playerObject->transform.position = glm::vec3(message->position.x, message->position.y, message->position.z);
			if (message->owner) {
				scene->current_player = playerObject;
			} else {
				scene->players.push_back(playerObject);
			}
			BombermanClient::instance->current_scene->add(playerObject);
		}
		break;
	}
}

void ActionQueueManager::consume()
{
	if (this->actions.size() > 0) {
		ActionQueueManager::mutex.lock();
		this->doAction(this->actions[0]);
		this->removeAction(this->actions[0]);
		ActionQueueManager::mutex.unlock();
	}
}
