#pragma once
#include "Shader.h"
#include "Texture.h"

enum GameState 
{
    GAME_ACTIVE,
    GAME_OVER
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

    // constructor/destructor
    Game(int width, int height);
    ~Game();
    void initText();
    void initdata();
    void Player();
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
};