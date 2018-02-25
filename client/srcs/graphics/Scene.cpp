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
	if (obj != NULL)
		this->gameObjects[obj->id] = obj;
}

void								Scene::remove(GameObject *obj)
{
	std::lock_guard<std::mutex> lock(mutex);
	if (this->gameObjects.count(obj->id) != 0)
		this->gameObjects.erase(obj->id);
}

void								Scene::_calculPhisics(void)
{
	//TODO by static Components


	std::map<long, GameObject*> cpy = std::map<long, GameObject*>(this->gameObjects);
	BoxCollider::Check3DCollisions(cpy);
	for (std::map<long, GameObject*>::iterator it = cpy.begin(); it != cpy.end(); it++) {
		GameObject *currentGameObject = it->second;
		//script calling

		if (currentGameObject->toDelete)
		{
			this->remove(currentGameObject);
			delete currentGameObject;
			continue;
		}

		Script *script = currentGameObject->GetComponent<Script>();
		if (script != NULL && script->frame != 0L) {
			script->Update();
		}
	}
}

void								Scene::_drawGameObjects(void)
{
	std::lock_guard<std::mutex> lock(mutex);
	for (std::map<long, GameObject*>::iterator it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
		GameObject *currentGameObject = it->second;

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
}

// ###############################################################
