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

unsigned int initdata()
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

	return VAO;
}

void Jump()
{

}

void Player()
{
	unsigned int VAO = initdata();	//need the VAO to bind vertex array after shder compilation

	Shader pShader;
	pShader.Compile("res/shaders/sprite.vs", "res/shaders/sprite.frag");
	glBindVertexArray(VAO);
	pShader.Bind();

	/*const char* file = "res/textures/cacodemon.png";
	int width = 300, height = 300, channels;

	unsigned char* data = SOIL_load_image(file, &width, &height, &channels, SOIL_CREATE_NEW_ID);
	Texture2D caco;
	caco.Generate(file, 300, 300, data);*/

	glDrawArrays(GL_TRIANGLES, 0, 6);


	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;
}

void Game::Render()
{
	Player();
}