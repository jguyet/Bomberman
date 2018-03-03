#include "Bomberman.hpp"
#include "network/Socket.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

MainMenuScene::MainMenuScene ( void )
{
	//CAMERA
	this->camera = new Camera();
	this->camera->setProjection(45.0f, BombermanClient::getInstance()->screen->canvas_width, BombermanClient::getInstance()->screen->canvas_height, 0.1f, 10.0f);
	this->camera->transform.position = glm::vec3(0,0,0);
	this->camera->transform.rotation = glm::vec3(0,0,0);
	this->camera->buildFPSProjection();

	this->interface = new MainMenuInterface();
	// Mix_PlayMusic(BombermanClient::getInstance()->music_menu, 1);

	KeyBoard::instance->addHandler("MainMenuScene", this);
	return ;
}

MainMenuScene::MainMenuScene ( MainMenuScene const & src )
{
	*this = src;
	return ;
}

MainMenuScene &				MainMenuScene::operator=( MainMenuScene const & rhs )
{
	return (*this);
}

MainMenuScene::~MainMenuScene ( void )
{
	delete this->interface;
	KeyBoard::instance->removeHandler("MainMenuScene");
	return ;
}

std::ostream &				operator<<(std::ostream & o, MainMenuScene const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

bool								MainMenuScene::select_local(void)
{
	BombermanClient::getInstance()->new_socket("", 0);
	BombermanClient::getInstance()->setCurrentScene<GameScene>(new GameScene("map_01"));
	return true;
}

void								MainMenuScene::select_settings(void)
{
	BombermanClient::getInstance()->setCurrentScene<GameScene>(new SettingScene());
}

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
	bool connected = BombermanClient::getInstance()->new_socket(ip, port);

	if (connected) {
		return true;
	}
	BombermanClient::getInstance()->delete_socket();
	return false;
}

void								MainMenuScene::handleUP(unsigned int key)
{
	if (key == SDL_SCANCODE_ESCAPE) {
		BombermanClient::getInstance()->stop();
	}
	if (key == SDL_SCANCODE_KP_ENTER || key == SDL_SCANCODE_RETURN) {
		switch(this->interface->current_position)
		{
			case 0:
				BombermanClient::getInstance()->setCurrentScene<SoloMenuScene>(new SoloMenuScene());
			break ;
			case 1:
				this->select_server();
			break;
			case 2:
				this->select_settings();
			break ;
			case 3:
			break;
			case 4:
				delete this;
				BombermanClient::getInstance()->stop();
			break ;
		}
	}
}

void								MainMenuScene::calculPhisics(void)
{
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
