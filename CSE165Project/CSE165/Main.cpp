
//GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

#include "Game.h"

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

Game Dino(WIDTH, HEIGHT);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// The MAIN function, from here we start the application and run the game loop
int main(int argc, char* argv[])
{
    // Init GLFW
    glfwInit();

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Dino game", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //initializing our game
    Dino.initdata();
    Dino.initText();
    Dino.initPos();
    Dino.initPosEnemy();
    Dino.initBackground();

    double lastTime = 0.0f;
    double deltaTime = 0.0f;
    //float timer = glfwGetTime();
    static double limfps = 1.0 / 60.0;

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        //limitint fps for more consist performance across devices
        double currentTime = glfwGetTime();
        deltaTime += (currentTime - lastTime)/limfps;
        lastTime = currentTime;

        while (deltaTime >= 0.5f) {
            Dino.Update(deltaTime);
            deltaTime--;
        }

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // Clear the colorbuffer
        glClear(GL_COLOR_BUFFER_BIT);
        Dino.Render();
 
        glfwSwapBuffers(window);
    }
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();

    return EXIT_SUCCESS;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) 
    {
        if (Dino.State == GAME_INACTIVE)
        {
            Dino.initPos();
            Dino.initPosEnemy();
            Dino.State = GAME_ACTIVE;
        }

        Dino.Keys[key] = true;
    }

    else
        Dino.Keys[key] = false;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}