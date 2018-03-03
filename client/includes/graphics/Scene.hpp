#ifndef SCENE_HPP
# define SCENE_HPP

# include "Bomberman.hpp"
# include <mutex>
# include <atomic>

struct GameObject_list {
	std::map<long, GameObject*> gameObjects;
};

class Scene
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											Scene( void );
		virtual								~Scene( void );
		// ####################################################################
		virtual void						calculPhisics(void) = 0;
		virtual void						drawGameObjects(void) = 0;
		// PUBLICS ############################################################
		void								add(GameObject *obj);
		void								remove(GameObject *obj);

		GameObject_list						*getGameObjects_list();
		std::map<long, GameObject*>			&getGameObjects();
		std::atomic<GameObject_list*>		list;
		//std::map<long, GameObject*>			gameObjects;
		Camera								*camera;
		// ####################################################################
	protected:
		// PROTECTED ##########################################################
		void								_calculPhisics(void);
		void								_drawGameObjects(void);
		// ####################################################################
	private:
		void								private_remove(GameObject *obj);

		std::map<long, GameObject*>			delete_list;
		std::vector<long>					delete_list_ids;
		std::mutex							mutex;
};

#endif
