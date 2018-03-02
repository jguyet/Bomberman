#include "client/Loader.hpp"

Loader::Loader ()
{
}

Loader::Loader ( Loader const & src )
{
	*this = src;
}

Loader &				Loader::operator=( Loader const & rhs )
{
	return (*this);
}

Loader::~Loader ()
{

}

std::ostream &				operator<<(std::ostream & o, Loader const & i)
{
	return (o);
}

void Loader::loadShaders()
{
	ShaderUtils::getInstance()->loadShader("canvas", "./assets/reserved/canvas.vert", "./assets/reserved/canvas.frag");
	ShaderUtils::getInstance()->loadShader("dir", "./assets/shaders/global.vert", "./assets/shaders/global.frag");
	ShaderUtils::getInstance()->loadShader("bomb", "./assets/shaders/bomb.vert", "./assets/shaders/bomb.frag");
	ShaderUtils::getInstance()->loadShader("player", "./assets/shaders/player.vert", "./assets/shaders/player.frag");
}

void Loader::loadModels()
{
	Model::load("canvas", ShaderUtils::getInstance()->get("canvas"), "assets/reserved/canvas.obj");

	//Player
	Model::load("bomberman", ShaderUtils::getInstance()->get("player"), "assets/bomberman_animations/test.obj");
	Model::load("bomberman2", ShaderUtils::getInstance()->get("player"), "assets/bomberman_animations/test.obj");
	Model::load("walk_0", ShaderUtils::getInstance()->get("player"), "assets/bomberman_animations/walk/3.obj");
	Model::load("walk_1", ShaderUtils::getInstance()->get("player"), "assets/bomberman_animations/walk/2.obj");
	Model::load("walk_2", ShaderUtils::getInstance()->get("player"), "assets/bomberman_animations/walk/1.obj");
	Model::load("walk_3", ShaderUtils::getInstance()->get("player"), "assets/bomberman_animations/walk/0.obj");
	//bomb
	Model::load("bomb", ShaderUtils::getInstance()->get("bomb"), "assets/bomb/bomb.obj");
	//textures
	Model::load("flamme_block", ShaderUtils::getInstance()->get("dir"), "assets/textures/blocks/Flamme.obj");
	Model::load("N64", ShaderUtils::getInstance()->get("dir"), "assets/textures/N64 Cube/N64 Cube.obj");
	Model::load("ice_block", ShaderUtils::getInstance()->get("dir"), "assets/textures/blocks/mur1.obj");
	Model::load("ground1", ShaderUtils::getInstance()->get("dir"), "assets/textures/blocks/sol1.obj");

	Model::load("brick", ShaderUtils::getInstance()->get("dir"), "assets/textures/grass.obj");
	Model::load("skybox", ShaderUtils::getInstance()->get("dir"), "assets/skybox/skybox2.obj");

	Model::load("bonus-bomb-up", ShaderUtils::getInstance()->get("dir"), "assets/textures/bonus/bomb-up.obj");
	Model::load("bonus-power-up", ShaderUtils::getInstance()->get("dir"), "assets/textures/bonus/power-up.obj");
	Model::load("bonus-speed-up", ShaderUtils::getInstance()->get("dir"), "assets/textures/bonus/speed-up.obj");

	Model::load("goomba", ShaderUtils::getInstance()->get("dir"), "assets/Goomba/goomba.obj");
}