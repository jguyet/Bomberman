#include "Bomberman.hpp"

// CANONICAL #####################################################

Scene::~Scene ( void )
{
	return ;
}

// ###############################################################

// PUBLIC METHOD #################################################

GameObject							*Scene::newGameObject(void)
{
	GameObject *obj = new GameObject();
	this->add(obj);
	return (obj);
}

void								Scene::add(GameObject *obj)
{
	this->gameObjects[obj->id] = obj;
}

void								Scene::remove(GameObject *obj)
{
	if (this->gameObjects.count(obj->id) != 0)
		this->gameObjects.erase(obj->id);
	delete obj;
}

void								Scene::_calculPhisics(void)
{
	for (std::map<long, GameObject*>::iterator it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
		GameObject *currentGameObject = it->second;
		//script calling
		Script *script = currentGameObject->GetComponent<Script>();
		if (script != NULL) {
			script->Update();
		}
	}
	//TODO by static Components
	BoxCollider::Check3DCollisions(this->gameObjects);
}

void								Scene::_drawGameObjects(void)
{
	for (std::map<long, GameObject*>::iterator it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
		GameObject *currentGameObject = it->second;
		//model drawing
		Model *model = currentGameObject->GetComponent<Model>();
		if (model != NULL) {
			model->draw(currentGameObject->transform.position, currentGameObject->transform.rotation, currentGameObject->transform.scale, this->camera->projectionMatrix, this->camera->viewMatrix);
		}
	}
}

// ###############################################################
