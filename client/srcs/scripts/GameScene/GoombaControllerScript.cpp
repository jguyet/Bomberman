#include "Bomberman.hpp"

// STATIC ########################################################

std::vector<GoombaControllerScript*> GoombaControllerScript::List = std::vector<GoombaControllerScript*>();

// ###############################################################

// CANONICAL #####################################################

GoombaControllerScript::GoombaControllerScript ( void )
{
	GoombaControllerScript::List.push_back(this);

	this->startTime = TimeUtils::getCurrentSystemMillis();
	this->anim_time = TimeUtils::getCurrentSystemMillis();
	this->sens = false;
	this->max_scale = -0.1f;
	this->min_scale = -0.05f;


	return ;
}

GoombaControllerScript::GoombaControllerScript ( GoombaControllerScript const & src )
{
	*this = src;
	return ;
}

GoombaControllerScript &				GoombaControllerScript::operator=( GoombaControllerScript const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GoombaControllerScript::~GoombaControllerScript ( void )
{
	GoombaControllerScript::List.erase(std::remove(GoombaControllerScript::List.begin(), GoombaControllerScript::List.end(), this));
	return ;
}

std::ostream &				operator<<(std::ostream & o, GoombaControllerScript const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void								GoombaControllerScript::Update(void)
{
/*	if (TimeUtils::getCurrentSystemMillis() < this->anim_time + 40L)
		return ;
	if (this->sens == false)
	{
		this->gameObject->transform.scale.x -= 0.01f;
		this->gameObject->transform.scale.y -= 0.01f;
		this->gameObject->transform.scale.z -= 0.01f;

		this->gameObject->transform.position.y += 0.01f;
		if (this->gameObject->transform.scale.x >= this->min_scale)
			this->sens = true;
	} else {
		this->gameObject->transform.scale.x += 0.01f;
		this->gameObject->transform.scale.y += 0.01f;
		this->gameObject->transform.scale.z += 0.01f;

		this->gameObject->transform.position.y -= 0.01f;
		if (this->gameObject->transform.scale.x <= this->max_scale)
			this->sens = false;
	}
	this->anim_time = TimeUtils::getCurrentSystemMillis();*/
}

void								GoombaControllerScript::OnPreRender(void)
{
/*
	float timer = 1.0f - ((this->startTime + BOMB_TIME - TimeUtils::getCurrentSystemMillis())/(float)BOMB_TIME);

	Model *bombObjectModel = this->gameObject->GetComponent<Model>();
	glUseProgram(bombObjectModel->shader);
	bombObjectModel->shaderBind = true;

	glm::vec3 colors = glm::vec3(timer,0.f,0.f);
	glUniform3fv(bombObjectModel->color,1 , &colors[0]);
*/
	//TODO add meche color in shader
}

void								GoombaControllerScript::OnEndRender(void)
{

}

// ###############################################################
