#include "Bomberman.hpp"
#include "network/Socket.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

MainMenuScene::MainMenuScene ( void )
{
	//CAMERA
	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::getInstance()->screen->width, BombermanClient::getInstance()->screen->height, 0.1f, 10.0f);
	this->camera->transform.position = glm::vec3(0,0,0);
	this->camera->transform.rotation = glm::vec3(0,0,0);
	this->camera->buildFPSProjection();

	this->interface = new MainMenuInterface();
	Mix_PlayMusic(BombermanClient::getInstance()->music_menu, 1);
	return ;
}

MainMenuScene::MainMenuScene ( MainMenuScene const & src )
{
	*this = src;
	return ;
}

MainMenuScene &				MainMenuScene::operator=( MainMenuScene const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

MainMenuScene::~MainMenuScene ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, MainMenuScene const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

bool								MainMenuScene::select_server(void)
{
	std::string network_addr = BombermanClient::getInstance()->properties->get("Network.address");
	std::vector<std::string> string_split = split(network_addr, ':');
	if (network_addr == "" || string_split.size() != 2)
	{
		std::cerr << "Unknow Network.address on properties file" << std::endl;
		return false;
	}
	std::string ip = string_split.at(0);
	int port = atoi(string_split.at(1).c_str());

	BombermanClient::getInstance()->sock = new Socket(ip.c_str(), port);

	if (BombermanClient::getInstance()->sock->state == true)
	{
		BombermanClient::getInstance()->current_scene = new GameScene("map_01");
		return true;
	}
	return false;
}

bool								MainMenuScene::select_local(void)
{
	BombermanClient::getInstance()->sock = new Socket("", 0);
	BombermanClient::getInstance()->current_scene = new GameScene("map_01");
	return true;
}

void								MainMenuScene::calculPhisics(void)
{
	if (KeyBoard::instance->getKey(SDL_SCANCODE_ESCAPE)) {//ESC
		BombermanClient::getInstance()->stop();
	}
	if (KeyBoard::instance->getKey(SDL_SCANCODE_KP_ENTER) || KeyBoard::instance->getKey(SDL_SCANCODE_RETURN)) {//ESC
		switch(this->interface->current_position)
		{
			case 0:
				this->select_local();
			break ;
			case 1:
				this->select_server();
			break;
		}
	}
	//call parent method
	this->_calculPhisics();
}

void								MainMenuScene::drawGameObjects(void)
{
	//build Matrixs
	this->camera->buildFPSProjection();
	//call parent method
	this->_drawGameObjects();
	//draw canvas
	this->interface->draw();
}
