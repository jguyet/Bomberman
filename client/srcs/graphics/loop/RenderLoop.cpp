#include "Bomberman.hpp"
#include "managers/ActionQueueManager.hpp"

// CANONICAL #####################################################

RenderLoop::RenderLoop ( IRenderLoop * r )
{
	this->renderloop = r;
	this->running = false;
	return ;
}

RenderLoop::RenderLoop ( RenderLoop const & src )
{
	*this = src;
	return ;
}

RenderLoop::~RenderLoop ( void )
{
	return ;
}

RenderLoop &				RenderLoop::operator=( RenderLoop const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

std::ostream &				operator<<(std::ostream & o, RenderLoop const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void						RenderLoop::start( void )
{
	if (this->running == true) {
		return ;
	}
	this->running = true;
	//thread controller
	std::thread threadcontroller(&RenderLoop::loopcontroller, this);
	//main thread for rendering
	this->looprender();

	threadcontroller.join();
}

void						RenderLoop::stop( void )
{
	if (this->running == false) {
		return ;
	}
	this->running = false;
}

void						RenderLoop::loopcontroller( void )
{
	long frames = 0;
	long lastTime = TimeUtils::getCurrentNanoSeconds();

	while (this->running) {
		long passedTime = TimeUtils::getCurrentNanoSeconds() - lastTime;

		if (passedTime >= this->controllerRate) {
			lastTime = TimeUtils::getCurrentNanoSeconds();
			this->renderloop->controllerLoop();
			frames++;
		} else {
			usleep(100);
		}
		if (frames >= 1000000000L) {
			frames = 0;
		}
	}
}

void						RenderLoop::looprender( void )
{
	long frames = 0;
	long lastTime = TimeUtils::getCurrentNanoSeconds();

	while (this->running) {
		long passedTime = TimeUtils::getCurrentNanoSeconds() - lastTime;

		if (passedTime >= this->renderRate) {
			ActionQueueManager::instance->consume();
			lastTime = TimeUtils::getCurrentNanoSeconds();
			this->renderloop->renderLoop();
			frames++;
		} else {
			usleep(100);
		}
		if (frames >= 1000000000L) {
			frames = 0;
		}
	}
}

// ###############################################################
