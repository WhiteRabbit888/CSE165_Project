#pragma once
#include "Shader.h"
#include "GameObject.h"

enum GameState 
{
    GAME_ACTIVE,
    GAME_INACTIVE,
};

class Game 
{
public:
    // game state
    GameState    State;
    bool         Keys[1024];
    int Width, Height;
    unsigned int VAO;

    Shader shader;
    unsigned int textures[2];

    GameObject *player;
    GameObject *enemy;

    // constructor/destructor
    Game(int width, int height);
    ~Game();
    void initText();
    void initdata();
    void initPos();
    void initPosEnemy();
    void Player();
    void Enemy();
    bool CheckCollision();
    void Jump(float dt);
    void spawnEnemy(float dt);
    void Update(float dt);
    void Draw(unsigned int texture, glm::vec2 pos, glm::vec2 size);
    void Render();
};