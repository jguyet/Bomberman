#include "managers/ActionQueueManager.hpp"
#include "models/ActionQueue.hpp"
#include "messages/MapSelectMessage.hpp"
#include "messages/NewPlayerMessage.hpp"
#include "messages/PlayerPositionMessage.hpp"
#include "messages/PlayersPositionMessage.hpp"
# include "messages/GameStartedMessage.hpp"
#include "messages/ActionMessage.hpp"
#include "messages/PlayerDeadMessage.hpp"

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

void	ActionQueueManager::removeAllActions(void)
{
	for (int i = 0; i < this->actions.size(); i++)
	{
		ActionQueue	*action = this->actions.at(i);

		delete action;
	}
	this->actions.clear();
}

void ActionQueueManager::doAction(ActionQueue *action)
{
	switch (action->messageId)
	{
		case MapSelectMessage::ID: {
			MapSelectMessage	*mapMessage = (MapSelectMessage*)action->message;
			GameScene* scene = BombermanClient::getInstance()->setCurrentScene<GameScene>(new GameScene(mapMessage->name));

			Case *spawn = scene->mapManager->getRandomWalkableCase(scene->map);
			if (spawn) {
				glm::vec3 pos = spawn->ground->transform.position;
				BombermanClient::getInstance()->sock->newPlayer(pos.x, 1, pos.z);
			} else {
				BombermanClient::getInstance()->sock->newPlayer(2, 1, 4);
			}
		}
		break;

		case NewPlayerMessage::ID: {
			NewPlayerMessage		*message = (NewPlayerMessage*)action->message;
			GameObject 				*playerObject = Factory::newPlayer(message->position.playerId);
			GameScene				*scene = BombermanClient::getInstance()->getCurrentScene<GameScene>();

			playerObject->transform.scale = glm::vec3(3,3,3);
			playerObject->transform.rotation = glm::vec3(0,0,0);
			playerObject->transform.position = glm::vec3(message->position.x, message->position.y, message->position.z);
			if (message->owner) {
				scene->current_player = playerObject;
			} else {
				scene->players.push_back(playerObject);
			}
			scene->all_player.push_back(playerObject);
			scene->add(playerObject);
		}
		break;

		case PlayersPositionMessage::ID: {
			PlayersPositionMessage	*message = (PlayersPositionMessage*)action->message;
			GameScene				*scene = BombermanClient::getInstance()->getCurrentScene<GameScene>();
			for (int i = 0; i < message->positions_length; i++) {
				PlayerPositionObject &object = message->positions[i];
				GameObject *player = scene->findPlayerById(object.playerId);
				if (player != NULL && player->GetComponent<Script>() != NULL && player != scene->current_player) {
					CharacterControllerScript *script = ((CharacterControllerScript*)player->GetComponent<Script>());

					script->Update();
					player->transform.position.x = object.x;
					player->transform.position.y = object.y;
					player->transform.position.z = object.z;
				}
			}
		}
		break;

		case ActionMessage::ID: {
			ActionObject	object = ((ActionMessage*)action->message)->action;
			GameScene		*scene = BombermanClient::getInstance()->getCurrentScene<GameScene>();
			if (object.type == ActionType::TYPE_BOMB) {
				Case *c = scene->map->getCase(object.x, object.z);
				if (c != NULL) {
					GameObject *player = scene->findPlayerById(((ActionMessage*)action->message)->byPlayer);
					if (player != NULL) {
						CharacterControllerScript *script = ((CharacterControllerScript*)player->GetComponent<Script>());
						GameObject *bomb = Factory::newBomb(script);
						bomb->transform.position = glm::vec3(c->position.x,c->position.y,c->position.z);
						bomb->transform.scale = glm::vec3(1.5f,1.5f,1.5f);
						bomb->transform.rotation = glm::vec3(0,0,0);
						scene->add(bomb);
						c->obstacle = bomb;
						script->last_bomb_2 = script->last_bomb_1;
						script->last_bomb_1 = bomb->id;
					}
				}
			}
			else
			{
				GameObject	*obj = new GameObject();
				obj->transform.position = glm::vec3(object.x * 2, 0, object.z * 2);
				obj->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);

				if (object.type == ActionType::TYPE_BONUS_POWER_UP) {
					obj->tag = "bonus-power-up";
					obj->AddComponent<Model>(Model::model["bonus-power-up"]);
				}
				else if (object.type == ActionType::TYPE_BONUS_SPEED_UP) {
					obj->tag = "bonus-speed-up";
					obj->AddComponent<Model>(Model::model["bonus-speed-up"]);
				}
				else if (object.type == ActionType::TYPE_BONUS_BOMB_UP) {
					obj->tag = "bonus-bomb-up";
					obj->AddComponent<Model>(Model::model["bonus-bomb-up"]);
				}
				scene->add(obj);
			}
		}
		break;

		case PlayerDeadMessage::ID: {
			PlayerDeadMessage	*message = (PlayerDeadMessage*)action->message;
			GameScene			*scene = BombermanClient::getInstance()->getCurrentScene<GameScene>();
			GameObject			*player = scene->findPlayerById(message->playerId);

			if (player != NULL)
			{
				scene->removePlayer(player);
			}
		}
		break;
	}
}

void ActionQueueManager::consume()
{
	if (BombermanClient::getInstance()->sock == NULL || BombermanClient::getInstance()->sock->state == false) {
		this->removeAllActions();
		return ;
	}
	if (this->actions.size() > 0) {
		ActionQueueManager::mutex.lock();
		this->doAction(this->actions[0]);
		this->removeAction(this->actions[0]);
		ActionQueueManager::mutex.unlock();
	}
}
