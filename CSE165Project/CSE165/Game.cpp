#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include <SOIL2.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game::Game(int width, int height) : State(GAME_INACTIVE), Keys(), Width(width), Height(height) 
{

}

Game::~Game()
{
	delete player;
	delete enemy;
}

void Game::initdata()
{
	unsigned int IBO, VBO;

	//rendering sprites as a rectangle comprised of two right triangles
	float positions[] = {
		//positions		//texture coordinates	//texture indices
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,		0.0f,		// top right
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f,		// bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f,		// bottom left
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,		0.0f,		// top left 

		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,		1.0f,		// top right
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		1.0f,		// bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		1.0f,		// bottom left
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,		1.0f		// top left 
	};
	//indexes our vertices 
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3,  // second triangle

		4, 5, 7,
		5, 6, 7
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	//textures
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	//texture indices
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
}

void Game::initText()
{
	shaders[0].Compile("res/shaders/background.vs", "res/shaders/background.fs");
	shaders[1].Compile("res/shaders/sprite.vs", "res/shaders/sprite.fs");
	shaders[2].Compile("res/shaders/enemy.vs", "res/shaders/enemy.fs");

	glGenTextures(3, textures);
	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);

	shaders[0].Bind();
	glUniform1i(glGetUniformLocation(shaders[0].ID, "background"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	unsigned char* data = SOIL_load_image("res/textures/background.png", &width, &height, &nrChannels, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	SOIL_free_image_data(data);

	shaders[1].Bind();
	glUniform1i(glGetUniformLocation(shaders[1].ID, "texture1"), 1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	data = SOIL_load_image("res/textures/cacodemon.png", &width, &height, &nrChannels, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	SOIL_free_image_data(data);

	shaders[2].Bind();
	glUniform1i(glGetUniformLocation(shaders[2].ID, "texture2"), 2);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	data = SOIL_load_image("res/textures/cactus.png", &width, &height, &nrChannels, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	SOIL_free_image_data(data);
}

void Game::initPos()
{
	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec2 size = glm::vec2(0.35f, 0.35f);
	glm::vec2 playerpos = glm::vec2(-2.0f * size.x, -2.0f * size.y);

	//initial location of player sprite
	transform = glm::translate(transform, glm::vec3(playerpos, 0.0f));
	transform = glm::scale(transform, glm::vec3(size, 1.0f)); 

	shaders[0].SetMatrix4("transform", transform);

	player = new GameObject(playerpos, size, textures[1], glm::vec2(0, 0.1f));
}

void Game::initPosEnemy()
{
	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec2 size = glm::vec2(0.15f, 0.15f);
	glm::vec2 enemypos = glm::vec2(7.0f * size.x, -5.0f * size.y);

	transform = glm::translate(transform, glm::vec3(enemypos, 0.0f));
	transform = glm::scale(transform, glm::vec3(size, 1.0f));

	shaders[1].SetMatrix4("transform", transform);

	enemy = new GameObject(enemypos, size, textures[2], glm::vec2(0.5f, 0.0f));
}

void Game::initBackground()
{
	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec2 size = glm::vec2(2.0f, 2.0f);

	transform = glm::translate(transform, glm::vec3(0.0f * size.x, 0.0f * size.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(size, 1.0f));

	glBindTexture(GL_TEXTURE_2D, textures[0]);

	shaders[2].SetMatrix4("transform", transform);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Game::Draw(unsigned int texture, Shader &shader, glm::vec2 pos, glm::vec2 size)
{
	glm::mat4 transform = glm::mat4(1.0f);	

	transform = glm::translate(transform, glm::vec3(pos.x, pos.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(size, 1.0f));

	shader.SetMatrix4("transform", transform);

	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

bool Game::CheckCollision()
{
	// collision x-axis?
	bool collisionX = player->Position.x + player->Size.x >= enemy->Position.x &&
		enemy->Position.x + enemy->Size.x >= player->Position.x;
	// collision y-axis?
	bool collisionY = player->Position.y + player->Size.y >= enemy->Position.y &&
		enemy->Position.y + enemy->Size.y >= player->Position.y;
	// collision only if on both axes
	return collisionX && collisionY;
}

void Game::spawnEnemy(float dt)
{
	if (enemy->Position.x >= -1.0f)
	{
		enemy->Position.x -= enemy->Velocity.x * dt;
		Draw(textures[2], shaders[2], enemy->Position, enemy->Size);
	}
	else
		initPosEnemy();
}

void Game::Jump(float dt)
{
	static bool falling = false;

	if (player->Position.y < 0.0f && !falling)
	{
		player->Position.y += player->Velocity.y * dt;
		Draw(textures[1], shaders[1], player->Position, player->Size);
	}
	else
		falling = true;

	if (player->Position.y >= -0.7f && falling)
	{
		player->Position.y -= player->Velocity.y * dt;
		Draw(textures[2], shaders[2], player->Position, player->Size);
	}
	else
		falling = false;
}

void Game::Update(float dt)
{
	static float timer = 50.0f;
	static bool jumping = false;
	static float spawnrate = 1.0f / 30.0f;

	if (this->State == GAME_ACTIVE)
	{
		if (this->Keys[GLFW_KEY_SPACE])
			jumping = true;

		if (jumping)
		{
			this->Jump(dt / 2.0f);

			if (timer-- <= 0)
			{
				timer = 50.0f;
				jumping = false;
				initPos();
			}
		}

		this->spawnEnemy(spawnrate);
	}
	if (CheckCollision())
		this->State = GAME_INACTIVE;
}

void Game::Render()
{
	initBackground();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	Draw(textures[1], shaders[1], player->Position, player->Size);
	Draw(textures[2], shaders[2],  enemy->Position, enemy->Size);
}