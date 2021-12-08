#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include <SOIL2.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game::Game(int width, int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) 
{

}

Game::~Game()
{

}

void Game::initdata()
{
	unsigned int IBO, VBO;

	shader.Compile("res/shaders/sprite.vs", "res/shaders/sprite.fs");

	float positions[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//textures
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Game::initText()
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	const char* file = "res/textures/cacodemon.png";
	unsigned char* data = SOIL_load_image(file, &width, &height, &nrChannels, SOIL_LOAD_AUTO);

	playertext.Generate(width, height, data);
	SOIL_free_image_data(data);
	shader.Bind();
	shader.SetInteger("texture1", 0);

	file = "res/textures/cacodemon.png";
	data = SOIL_load_image(file, &width, &height, &nrChannels, SOIL_LOAD_AUTO);

	enemytext.Generate(width, height, data);
	SOIL_free_image_data(data);
	shader.Bind();
	shader.SetInteger("texture1", 0);
}

void Game::initPos()
{
	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec2 size = glm::vec2(0.35f, 0.35f);
	glm::vec2 playerpos = glm::vec2(-2.0f * size.x, -2.0f * size.y);

	//initial location of player sprite
	transform = glm::translate(transform, glm::vec3(playerpos, 0.0f));
	transform = glm::scale(transform, glm::vec3(size, 1.0f)); 

	shader.SetMatrix4("transform", transform);

	glActiveTexture(GL_TEXTURE0);
	playertext.Bind();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	player = new GameObject(playerpos, size, playertext, glm::vec2(0, 1.0f));
}

void Game::initPosEnemy()
{
	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec2 size = glm::vec2(0.15f, 0.15f);
	glm::vec2 enemypos = glm::vec2(4.0f * size.x, -5.0f * size.y);

	transform = glm::translate(transform, glm::vec3(enemypos, 0.0f));
	transform = glm::scale(transform, glm::vec3(size, 1.0f));

	shader.SetMatrix4("transform", transform);

	glActiveTexture(GL_TEXTURE1);
	enemytext.Bind();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	enemy = new GameObject(enemypos, size, enemytext, glm::vec2(0.5f, 0.0f));
}

void Game::Draw(Texture2D & sprite, glm::vec2 pos, glm::vec2 size)
{
	glm::mat4 transform = glm::mat4(1.0f);	

	transform = glm::translate(transform, glm::vec3(pos.x, pos.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(size, 1.0f)); // last scale

	shader.SetMatrix4("transform", transform);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Game::spawnEnemy(float dt)
{
	if (enemy->Position.x >= -2.0f)
	{
		enemy->Position.x -= dt;
		Draw(enemytext, enemy->Position, enemy->Size);
	}
	else
		initPosEnemy();
}

void Game::Jump(float dt)
{
	static bool falling = false;

	if (player->Position.y < -0.10f && !falling)
	{
		player->Position.y += player->Velocity.y * dt;
		Draw(playertext, player->Position, player->Size);
	}
	else
		falling = true;

	if (player->Position.y >= -0.7f && falling)
	{
		player->Position.y -= player->Velocity.y * dt;
		Draw(playertext, player->Position, player->Size);
	}
	else
		falling = false;
}

void Game::Update(float dt)
{
	static float timer = 600.0f;
	static bool jumping = false;

	if (this->Keys[GLFW_KEY_SPACE])
		jumping = true;

	if (jumping)
	{
		this->Jump(dt);

		if (timer-- == 0)
		{
			timer = 600.0f;
			jumping = false;
			initPos();
		}
	}
	this->spawnEnemy(dt);
}

void Game::Player()
{
	glActiveTexture(GL_TEXTURE0);
	playertext.Bind();

	shader.Bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Game::Render()
{
	Player();
	Draw(playertext, player->Position, player->Size);
}