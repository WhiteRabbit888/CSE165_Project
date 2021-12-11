#include <glm/glm.hpp>
#include "Texture.h"

class GameObject
{
public:
	// object state
	glm::vec2   Position, Size, Velocity;

	// render state
	unsigned int SpriteID;
	// constructor(s)
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, unsigned int spriteID, glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
};