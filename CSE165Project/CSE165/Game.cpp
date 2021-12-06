#include "Game.h"
#include "GameObject.h"

Renderer *renderer;
GameObject *Player;

Game::Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

Game::~Game()
{
	delete renderer;
	delete Player;
}

void Game::Init()
{
	ResourceManager::LoadShader("res/shaders/sprite.vs", "res/shaders/sprite.frag", "sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Width),
		static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Bind().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	//Shader shader = ResourceManager::GetShader("sprite");
	renderer = new Renderer(ResourceManager::GetShader("sprite"));

	ResourceManager::LoadTexture("res/textures/cacodemon.png", true, "caco");
}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		//if(this->Keys[GLFW_KEY_SPACE])
	}
}

void Game::Render()
{
	//Texture2D text = ResourceManager::GetTexture("caco");
	renderer->Draw(ResourceManager::GetTexture("caco"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}