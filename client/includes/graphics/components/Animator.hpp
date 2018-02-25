#ifndef ANIMATOR_HPP
# define ANIMATOR_HPP

# include "Bomberman.hpp"

class Animator : public Component
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
													Animator( void );
													Animator( Animator const & src );
		virtual										~Animator( void );
		Animator &									operator=( Animator const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, Animator const & i);
		// PUBLICS ############################################################
		void										newAnimation(const char *key, long time_between_animation, int number_of_models, ...);
		void										handleAnimation(const char *key);
		void										removeAnimation(const char *key);
		Model										*build(void);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		void										loadNextAnimation(const char *key);

		const char 									*next_animation;

		std::map<const char*, std::map<int, Model*>>	animations;
		std::map<const char*, int>					animations_time;
		const char 									*current_animation;
		int											current_animation_frame_time;
		int											current_animation_id;
		long										last_handled_animation_time;
		// ####################################################################

};

#endif
