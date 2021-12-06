#include "Game.h"
#include <SOIL2.h>

Renderer *renderer;
//GameObject *Player;

Game::Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

Game::~Game()
{
	delete renderer;
}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		//if(this->Keys[GLFW_KEY_SPACE])
	}
}

void Player()
{
	unsigned int VAO, VBO;
	float positions[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Shader pShader;
	pShader.Compile("res/shaders/sprite.vs", "res/shaders/sprite.fs");
	pShader.Bind();
}

void Game::Render()
{
	
}