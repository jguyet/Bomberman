#ifndef SCENE_HPP
# define SCENE_HPP

# include "Bomberman.hpp"
# include <mutex>
# include <atomic>
# include <unordered_map>

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

		Camera								*camera;
		std::unordered_map<long, GameObject*>			gameObjects;
		std::unordered_map<long, GameObject*>			gameObjects_script;
		// ####################################################################
	protected:
		// PROTECTED ##########################################################
		void								_calculPhisics(void);
		void								_drawGameObjects(void);
		// ####################################################################
	private:
		void								remove_toDelete( int number );
		void								remove_all_toDelete( void );
		bool								check_gameObject_toDelete(GameObject *obj);

		std::map<long, GameObject*>			delete_list;
		std::vector<long>					delete_list_ids;
		std::mutex							mutex;
};

#endif
