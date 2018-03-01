#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

# include "Bomberman.hpp"

struct Transform {
	glm::vec3			position = glm::vec3(0,0,0);
	glm::vec3			rotation = glm::vec3(0,0,0);
	glm::vec3			scale = glm::vec3(1,1,1);

	friend std::ostream &					operator<<(std::ostream & o, Transform const & i)
	{
		o << "position vec3(" << i.position.x << "," << i.position.y << "," << i.position.z << ")" << std::endl;
		o << "rotation vec3(" << i.rotation.x << "," << i.rotation.y << "," << i.rotation.z << ")" << std::endl;
		o << "scale    vec3(" << i.scale.x << "," << i.scale.y << "," << i.scale.z << ")";
		return (o);
	}
};

class GameObject
{
	public:
		// STATICS #############################################################
		static long								uid;
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
		template <typename T> bool				AddComponent(void);
		template <typename T> T					*GetComponent(void);
		template <typename T> bool				RemoveComponent(void);

		Transform								transform;
		long									id;
		std::string								tag;
		bool 									toDelete = false;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		std::map<std::string, Component*>	components;
		// #####################################################################
};

// TPP METHODS #################################################################
template <typename T>
bool						GameObject::AddComponent(Component *component)
{
	std::string name = std::string(typeid(T).name());
	name.erase(std::remove_if(name.begin(), name.end(), &isdigit), name.end());
	this->components[name] = component;
	component->gameObject = this;
	return true;
}

template <typename T>
bool						GameObject::AddComponent( void )
{
	std::string name = std::string(typeid(T).name());
	name.erase(std::remove_if(name.begin(), name.end(), &isdigit), name.end());
	T *component = new T();
	this->components[name] = component;
	component->gameObject = this;
	return true;
}

template <typename T>
bool						GameObject::RemoveComponent(void)
{
	std::string name = std::string(typeid(T).name());
	name.erase(std::remove_if(name.begin(), name.end(), &isdigit), name.end());
	if (this->components.count(name) == 0) {
		return false;
	}
	this->components[name] = NULL;
	return true;
}

template<typename T>
T*							GameObject::GetComponent(void)
{
	std::string name = std::string(typeid(T).name());
	name.erase(std::remove_if(name.begin(), name.end(), &isdigit), name.end());
	if (this->components.count(name) == 0) {
		return NULL;
	}
	return dynamic_cast<T*>(this->components[name]);
}
// #############################################################################
#endif
