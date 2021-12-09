#pragma once
#include "Shader.h"
#include "Texture.h"
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

    Texture2D playertext;
    Texture2D enemytext;

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
    void Jump(float dt);
    void spawnEnemy(float dt);
    void Update(float dt);
    void Draw(Texture2D& sprite, Shader& shader, glm::vec2 pos, glm::vec2 size);
    void Render();
};