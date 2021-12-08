#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include <SOIL2.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

Game::Game(int width, int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) 
{

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

	glm::vec2 size = glm::vec2(0.35f, 0.35f);

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(-2.0f * size.x, -2.0f * size.y, 0.0f));

	transform = glm::scale(transform, glm::vec3(size, 1.0f));
	
	unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

}

Game::~Game()
{

}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		//if(this->Keys[GLFW_KEY_SPACE])
	}
}

void Game::initdata()
{
	unsigned int IBO, VBO;

	shader.Compile("res/shaders/sprite.vs", "res/shaders/sprite.fs");

	float positions[] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
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

void Jump()
{

}

void Game::Player()
{
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	playertext.Bind();
	shader.Bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Game::Render()
{
	Player();
}