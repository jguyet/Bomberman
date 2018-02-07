#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

# include "Bomberman.hpp"

struct Transform {
	glm::vec3			position = glm::vec3(0,0,0);
	glm::vec3			rotation = glm::vec3(0,0,0);
	glm::vec3			scale = glm::vec3(1,1,1);
};

class GameObject
{
	public:
		// STATICS #############################################################
		// #####################################################################
		// CANONICAL ###########################################################
												GameObject( void );
												GameObject( GameObject const & src );
		virtual									~GameObject( void );
		GameObject &							operator=( GameObject const & rhs );
		friend std::ostream &					operator<<(std::ostream & o, GameObject const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		void									Translate(glm::vec3 v);
		template <typename T> bool				AddComponent(Component *component);
		template <typename T> T					*GetComponent(void);
		template <typename T> bool				RemoveComponent(void);
		void									ProcessRenderingComponents(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix);
		void									ProcessPhisicsComponents(void);

		Transform								transform;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		std::map<const std::string, Component*>	components;
		// #####################################################################
};

// TPP METHODS #################################################################
template <typename T>
bool						GameObject::AddComponent(Component *component)
{
	const char* name = typeid(T).name();
	this->components[name] = component;
	return true;
}

template <typename T>
bool						GameObject::RemoveComponent(void)
{
	const char* name = typeid(T).name();
	if (this->components.count(name) == 0) {
		return false;
	}
	this->components[name] = NULL;
	return true;
}

template<typename T>
T*							GameObject::GetComponent(void)
{
	const char* name = typeid(T).name();
	if (this->components.count(name) == 0) {
		return NULL;
	}
	return dynamic_cast<T*>(this->components[name]);
}
// #############################################################################
#endif
