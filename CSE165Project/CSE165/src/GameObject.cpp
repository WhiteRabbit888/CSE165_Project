#include "GameObject.h"

#include <glad/glad.h>

GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Sprite() { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Sprite(sprite) { }

void GameObject::Draw(Renderer& renderer)
{
    //renderer.Draw(this->Sprite, this->Position, this->Size, this->Color);
}