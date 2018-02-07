#ifndef BLOCK_HPP
# define BLOCK_HPP

# include "Bomberman.hpp"

class Block : public IModel
{
	public:
		// STATICS #############################################################
		// #####################################################################
		// CANONICAL ###########################################################
											Block( Model *model );
											Block( Block const & src );
		virtual								~Block( void );
		Block &								operator=( Block const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Block const & i);
		// #####################################################################
		// @OVERRIDE IModel ####################################################
		void								render(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix);
		// GameObject						gameObject;
		// #####################################################################
		// PUBLICS #############################################################
		// #####################################################################
	private:
		// PRIVATES ############################################################
		// #####################################################################
};

#endif
