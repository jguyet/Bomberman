#include "Bomberman.hpp"

// CANONICAL #####################################################
Scene::Scene( void )
{

}

Scene::~Scene ( void )
{
	for (auto &it : this->gameObjects) {
		GameObject *obj = it.second;

		if (obj == NULL)
			continue ;
		obj->toDelete = true;
		this->check_gameObject_toDelete(obj);
	}
	this->remove_all_toDelete();
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

void								Scene::_calculPhisics(void)
{
	//TODO by static Components
	BoxCollider::Check3DCollisions(this->gameObjects);

	for (auto &it : this->gameObjects) {
		GameObject *currentGameObject = it.second;
		//script calling
		if (this->check_gameObject_toDelete(currentGameObject))
			continue;
		Script *script = currentGameObject->GetComponent<Script>();
		if (script != NULL && script->frame != 0L) {
			script->Update();
		}
		if (this->check_gameObject_toDelete(currentGameObject))
			continue;
	}

	this->remove_all_toDelete();
}

void								Scene::_drawGameObjects(void)
{
	//lock GameObject map
	this->mutex.lock();
	for (auto &it : this->gameObjects) {
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

// PRIVATE #######################################################

bool								Scene::check_gameObject_toDelete(GameObject *obj)
{
	if (obj->toDelete) {
		this->delete_list[obj->id] = obj;
		this->delete_list_ids.push_back(obj->id);
		return true;
	}
	return false;
}

void								Scene::remove_all_toDelete( void )
{

	if (this->delete_list_ids.size() > 0) {
		this->mutex.lock();
		for (int i = 0; i < this->delete_list_ids.size(); i++) {
			long id = this->delete_list_ids.at(i);

			if (this->delete_list.count(id) == 0)
				continue ;
			GameObject *obj = this->delete_list[id];

			if (this->gameObjects.count(obj->id) != 0) {
				this->gameObjects.erase(obj->id);
				delete obj;
			}
		}
		this->delete_list.clear();
		this->delete_list_ids.clear();
		this->mutex.unlock();
	}
}

// ###############################################################
