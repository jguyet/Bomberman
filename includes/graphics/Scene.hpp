#ifndef SCENE_HPP
# define SCENE_HPP

# include "Bomberman.hpp"

class Scene
{
	public:

		virtual								~Scene( void );
		//virtual Scene &						operator=( Scene const & rhs ) = 0;

		virtual void						calculPhisics(void) = 0;
		virtual void						drawGameObjects(void) = 0;

		GameObject							*newGameObject(void);
		void								add(GameObject *obj);
		void								remove(GameObject *obj);

		std::map<long, GameObject*>			gameObjects;
		Camera								*camera;

	protected:
		void								_calculPhisics(void);
		void								_drawGameObjects(void);
};

#endif
