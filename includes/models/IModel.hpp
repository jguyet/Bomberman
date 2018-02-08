#ifndef IMODEL_HPP
# define IMODEL_HPP

# include "Bomberman.hpp"

class IModel
{
	public:
		// RENDER METHOD
		virtual void			render(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix) = 0;

		// Have Default GameObject
		GameObject				gameObject;
};

#endif
