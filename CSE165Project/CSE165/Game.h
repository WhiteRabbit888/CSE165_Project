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

    Shader shaders[3];
    unsigned int textures[3];

    GameObject *player;
    GameObject *enemy;

    // constructor/destructor
    Game(int width, int height);
    virtual ~Game();
    void initText();
    void initdata();
    void initPos();
    void initPosEnemy();
    void initBackground();
    bool CheckCollision();
    void Jump(float dt);
    void spawnEnemy(float dt);
    void Update(float dt);
    void Draw(unsigned int texture, Shader &shader, glm::vec2 pos, glm::vec2 size);
    void Render();
};