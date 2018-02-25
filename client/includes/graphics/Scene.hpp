#ifndef SCENE_HPP
# define SCENE_HPP

# include "Bomberman.hpp"
# include <mutex>

class Scene
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
		virtual								~Scene( void );
		// ####################################################################
		virtual void						calculPhisics(void) = 0;
		virtual void						drawGameObjects(void) = 0;
		// PUBLICS ############################################################
		GameObject							*newGameObject(void);
		void								add(GameObject *obj);
		void								remove(GameObject *obj);

		std::map<long, GameObject*>			gameObjects;
		Camera								*camera;
		// ####################################################################
	protected:
		// PROTECTED ##########################################################
		void								_calculPhisics(void);
		void								_drawGameObjects(void);
		// ####################################################################
	private:
		std::vector<GameObject*>			delete_list;
		std::mutex							mutex;
};

#endif
