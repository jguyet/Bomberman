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
	while (this->lock) {usleep(10);}
	this->lock = true;
	if (this->gameObjects.count(obj->id) != 0)
		this->gameObjects.erase(obj->id);
	this->lock = false;
}

void								Scene::_calculPhisics(void)
{
	//TODO by static Components
	BoxCollider::Check3DCollisions(this->gameObjects);

	std::map<long, GameObject*> cpy = std::map<long, GameObject*>(this->gameObjects);

	for (std::map<long, GameObject*>::iterator it = cpy.begin(); it != cpy.end(); it++) {
		GameObject *currentGameObject = it->second;
		//script calling
		Script *script = currentGameObject->GetComponent<Script>();
		if (script != NULL && script->frame != 0L) {
			script->Update();
		}
	}
}

void								Scene::_drawGameObjects(void)
{
	//if locked wait
	while (this->lock) {usleep(10);}
	this->lock = true;
	for (std::map<long, GameObject*>::iterator it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
		GameObject *currentGameObject = it->second;

		Script *script = currentGameObject->GetComponent<Script>();

		if (script != NULL) {
			if (script->frame == 0L) {
				script->Start();
			}
			script->frame++;
		}
		//before rendering
		if (script != NULL) {
			script->OnPreRender();
		}
		//model rendering
		Model *model = currentGameObject->GetComponent<Model>();
		if (model != NULL) {
			model->draw(currentGameObject->transform.position, currentGameObject->transform.rotation, currentGameObject->transform.scale, this->camera->projectionMatrix, this->camera->viewMatrix);
		}
		//after rendering
		if (script != NULL) {
			script->OnEndRender();
		}
	}
	this->lock = false;
}

// ###############################################################
