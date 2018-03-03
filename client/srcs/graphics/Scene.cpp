#include "Bomberman.hpp"

// CANONICAL #####################################################
Scene::Scene( void )
{
	this->list = new GameObject_list();
}

Scene::~Scene ( void )
{
	std::map<long, GameObject*> &gameObjects = this->getGameObjects();

	for (std::map<long, GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++) {
		GameObject *obj = it->second;
		if (obj == NULL) {
			continue ;
		}
		delete obj;
		it->second = NULL;
	}
	gameObjects.clear();
	delete this->camera;
	return ;
}

// ###############################################################

// PUBLIC METHOD #################################################

GameObject_list						*Scene::getGameObjects_list()
{
	return (this->list);
}

std::map<long, GameObject*>			&Scene::getGameObjects()
{
	return (getGameObjects_list()->gameObjects);
}

void								Scene::add(GameObject *obj)
{
	std::map<long, GameObject*> &gameObjects = this->getGameObjects();

	if (obj != NULL)
		gameObjects[obj->id] = obj;
}

void								Scene::remove(GameObject *obj)
{
	obj->toDelete = true;
}

void								Scene::private_remove(GameObject *obj)
{
	this->mutex.lock();
	std::map<long, GameObject*> &gameObjects = this->getGameObjects();

	if (gameObjects.count(obj->id) != 0)
		gameObjects.erase(obj->id);
	this->mutex.unlock();
}

void								Scene::_calculPhisics(void)
{
	//TODO by static Components
	std::map<long, GameObject*> &gameObjects = this->getGameObjects();

	BoxCollider::Check3DCollisions(gameObjects);

	for (auto &it : gameObjects) {
		GameObject *currentGameObject = it.second;
		//script calling
		if (currentGameObject->toDelete) {
			this->delete_list[currentGameObject->id] = currentGameObject;
			this->delete_list_ids.push_back(currentGameObject->id);
			continue;
		}
		Script *script = currentGameObject->GetComponent<Script>();
		if (script != NULL && script->frame != 0L) {
			script->Update();
		}
		if (currentGameObject->toDelete) {
			this->delete_list[currentGameObject->id] = currentGameObject;
			this->delete_list_ids.push_back(currentGameObject->id);
			continue;
		}
	}
	if (this->delete_list_ids.size() > 0) {
		//this->mutex.lock();
		std::cout << "COUCOU" << std::endl;
		for (int i = 0; i < this->delete_list_ids.size(); i++) {
			long id = this->delete_list_ids.at(i);

			std::cout << "COUCOU" << std::endl;
			if (this->delete_list.count(id) == 0)
				continue ;
			GameObject *currentGameObject = this->delete_list[id];
			this->private_remove(currentGameObject);
			this->delete_list.erase(currentGameObject->id);
			delete currentGameObject;
		}
		this->delete_list.clear();
		this->delete_list_ids.clear();
		//this->mutex.unlock();
	}
}

void								Scene::_drawGameObjects(void)
{
	//lock GameObject map
	this->mutex.lock();
	std::map<long, GameObject*> &gameObjects = this->getGameObjects();

	for (auto &it : gameObjects) {
		GameObject *currentGameObject = it.second;

		Script *script = currentGameObject->GetComponent<Script>();
		Animator *animator = currentGameObject->GetComponent<Animator>();
		Model *model = currentGameObject->GetComponent<Model>();

		if (script != NULL) {
			if (script->frame == 0L) {
				script->Start();
			}
			script->frame++;
		}
		if (animator != NULL) {
			model = animator->build();
		}
		//before rendering
		if (script != NULL) {
			script->OnPreRender();
		}
		//model rendering
		if (model != NULL) {
			model->draw(currentGameObject->transform.position, currentGameObject->transform.rotation, currentGameObject->transform.scale, this->camera->projectionMatrix, this->camera->viewMatrix);
		}
		//after rendering
		if (script != NULL) {
			script->OnEndRender();
		}
	}
	this->mutex.unlock();
}

// ###############################################################
