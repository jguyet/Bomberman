#include "Bomberman.hpp"

// CANONICAL #####################################################
Scene::Scene( void )
{

}

Scene::~Scene ( void )
{
	for (std::map<long, GameObject*>::iterator it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
		GameObject *obj = it->second;
		if (obj == NULL) {
			continue ;
		}
		delete obj;
		it->second = NULL;
	}
	this->gameObjects.clear();
	delete this->camera;
	return ;
}

// ###############################################################

// PUBLIC METHOD #################################################

void								Scene::add(GameObject *obj)
{
	if (obj != NULL)
		this->gameObjects[obj->id] = obj;
}

void								Scene::remove(GameObject *obj)
{
	obj->toDelete = true;
}

void								Scene::private_remove(GameObject *obj)
{
	this->mutex.lock();
	if (this->gameObjects.count(obj->id) != 0)
		this->gameObjects.erase(obj->id);
	this->mutex.unlock();
}

void								Scene::_calculPhisics(void)
{
	//TODO by static Components
	BoxCollider::Check3DCollisions(this->gameObjects);

	for (std::map<long, GameObject*>::iterator it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
		GameObject *currentGameObject = it->second;
		//script calling
		if (currentGameObject->toDelete) {
			this->delete_list.push_back(currentGameObject);
			continue;
		}
		Script *script = currentGameObject->GetComponent<Script>();
		if (script != NULL && script->frame != 0L) {
			script->Update();
		}
		if (currentGameObject->toDelete) {
			this->delete_list.push_back(currentGameObject);
			continue;
		}
	}

	while (this->delete_list.size() > 0) {
		GameObject *currentGameObject = this->delete_list.at(0);
		this->private_remove(currentGameObject);
		this->delete_list.erase(this->delete_list.begin());
		delete currentGameObject;
	}
	this->delete_list.clear();
}

void								Scene::_drawGameObjects(void)
{
	this->mutex.lock();
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
	this->mutex.unlock();
}

// ###############################################################
