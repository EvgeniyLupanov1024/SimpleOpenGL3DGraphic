#include <iostream>
#include <string>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void init();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLFWwindow* window;
int width = 1000;
int height = 600;
char title[] = "Potitle";

const GLfloat g_vertex_illuminati[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f,
};

int main()
{
    init();

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.91f, 0.85f, 0.73f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void init() 
{    
    if (glfwInit() != GLFW_TRUE) {
        throw std::runtime_error("glfw not init");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("Failed to create GLFW window" );
    }
    glfwMakeContextCurrent(window);

    glViewport(0, 0, width, height);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("glew not init");
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
    }
}
