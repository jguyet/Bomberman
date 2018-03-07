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
	if (obj == NULL)
		return ;
	if (this->gameObjects.count(obj->id) != 0)
		return ;
	if (obj->GetComponent<Script>() != NULL)
		this->gameObjects_script[obj->id] = obj;
	this->gameObjects[obj->id] = obj;
}

void								Scene::remove(GameObject *obj)
{
	if (obj == NULL)
		return ;
	obj->toDelete = true;
}

void								test()
{

}

void								Scene::_calculPhisics(void)
{
	//TODO by static Components
	this->mutex.lock();
	BoxCollider::Check3DCollisions(this->gameObjects);

	for (auto const &it : this->gameObjects_script) {
		GameObject		*currentGameObject	= it.second;
		//script calling
		if (currentGameObject->toDelete)
			continue ;
		Script *script = currentGameObject->GetComponent<Script>();

		if (script == NULL) {
			continue ;
		}
		if (script->frame != 0L) {
			script->Update();
		}
	}
	this->mutex.unlock();
}

void								Scene::_drawGameObjects(void)
{
	//lock GameObject map
	for (auto const &it : this->gameObjects) {
		GameObject *currentGameObject = it.second;

		this->check_gameObject_toDelete(currentGameObject);
		if (currentGameObject->toDelete)
			continue ;

		Script		*script		= currentGameObject->GetComponent<Script>();
		Animator	*animator	= currentGameObject->GetComponent<Animator>();
		Model		*model		= currentGameObject->GetComponent<Model>();

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
	this->remove_toDelete(5);
}

// ###############################################################

// PRIVATE #######################################################

bool								Scene::check_gameObject_toDelete(GameObject *obj)
{
	if (obj->toDelete && this->delete_list.count(obj->id) == 0) {
		this->delete_list[obj->id] = obj;
		this->delete_list_ids.push_back(obj->id);
		return true;
	}
	return false;
}

void								Scene::remove_toDelete( int number )
{
	if (this->delete_list_ids.size() == 0)
		return ;
	this->mutex.lock();
	for (int i = 0; i < this->delete_list_ids.size() && i < number; i++) {
		long id = this->delete_list_ids.at(i);

		if (this->delete_list.count(id) == 0)
			continue ;
		GameObject *obj = this->delete_list[id];

		if (this->gameObjects.count(obj->id) != 0) {
			this->gameObjects.erase(obj->id);
			this->delete_list.erase(obj->id);
			this->gameObjects_script.erase(obj->id);
			this->delete_list_ids.erase(this->delete_list_ids.begin() + i);
			delete obj;
		}
	}
	this->mutex.unlock();
}

void								Scene::remove_all_toDelete( void )
{

	if (this->delete_list_ids.size() == 0)
		return ;
	this->mutex.lock();
	for (int i = 0; i < this->delete_list_ids.size(); i++) {
		long id = this->delete_list_ids.at(i);

		if (this->delete_list.count(id) == 0)
			continue ;
		GameObject *obj = this->delete_list[id];

		if (this->gameObjects.count(obj->id) != 0) {
			this->gameObjects.erase(obj->id);
			this->gameObjects_script.erase(obj->id);
			delete obj;
		}
	}
	this->delete_list.clear();
	this->delete_list_ids.clear();
	this->mutex.unlock();
}

// ###############################################################
