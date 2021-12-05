#include "Game.h"

Game::Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

Game::~Game()
{
}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		if(this->Keys[GLFW_KEY_SPACE])
	}
}
