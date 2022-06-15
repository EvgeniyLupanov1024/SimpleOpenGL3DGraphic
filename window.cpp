#include <iostream>
#include <string>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"

using namespace std;

void init();
void fillScene();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLFWwindow* window;
int width = 1000;
int height = 600;
char title[] = "Potitle";

int main()
{
    init();

    Shader ShProxy = Shader("proxy.vert", "proxy.frag");

    fillScene();

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.91f, 0.85f, 0.73f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ShProxy.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void init() 
{    
    if (glfwInit() != GLFW_TRUE) {
        throw runtime_error("GLFW not init");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        throw runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);

    glViewport(0, 0, width, height);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw runtime_error("GLEW not init");
    }
}

void fillScene()
{
    GLfloat g_vertex_illuminati[] = {
        -0.3f, -0.5f, 0.0f,
        0.3f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
    };

    GLuint VAO; 
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 

    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_illuminati), g_vertex_illuminati, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
