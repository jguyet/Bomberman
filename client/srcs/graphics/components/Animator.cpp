#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Animator::Animator ( void )
{
	this->current_animation = NULL;
	this->next_animation = NULL;
	return ;
}

Animator::Animator ( Animator const & src )
{
	*this = src;
	return ;
}

Animator &					Animator::operator=( Animator const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Animator::~Animator ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Animator const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						Animator::newAnimation(const char *key, long time_between_animation, int number_of_models, ...)
{
	this->animations[key] = std::map<int, Model*>();
	this->animations_time[key] = time_between_animation;

	void		*ptr;
	Model		*model;
	va_list		lst;
	int			i = 0;

	va_start(lst, number_of_models);
	while (i < number_of_models) {
		//models
		ptr = va_arg(lst,void*);
		model = reinterpret_cast<Model*>(ptr);
		this->animations[key][i] = model;
		i++;
	}
	va_end(lst);
}

void						Animator::handleAnimation(const char *key)
{
	if (this->animations.count(key) == 0)
		return ;
	if (this->current_animation == key || this->next_animation != NULL)
		return ;
	this->next_animation = key;
}

Model						*Animator::build(void)
{
	Model *current_animated_model;

	if (this->next_animation != NULL) {
		this->loadNextAnimation(this->next_animation);
		this->next_animation = NULL;
	}
	if (this->current_animation == NULL) {
		return NULL;
	}
	if (TimeUtils::getCurrentSystemMillis() > this->last_handled_animation_time + this->current_animation_frame_time) {
		this->current_animation_id++;
		this->last_handled_animation_time = TimeUtils::getCurrentSystemMillis();
		if (this->current_animation_id >= this->animations[this->current_animation].size() - 1)
			this->current_animation_id = 0;
	}
	current_animated_model = this->animations[this->current_animation][this->current_animation_id];
	this->gameObject->AddComponent<Model>(current_animated_model);
	return (current_animated_model);
}

void						Animator::removeAnimation(const char *key)
{
	if (this->animations.count(key) == 0)
		return ;
	this->animations.erase(key);
	this->animations_time.erase(key);
}

// ###############################################################

void						Animator::loadNextAnimation(const char *key)
{
	this->last_handled_animation_time = 0;
	this->current_animation = key;
	this->current_animation_id = 0;
	this->current_animation_frame_time = this->animations_time[key];
}
