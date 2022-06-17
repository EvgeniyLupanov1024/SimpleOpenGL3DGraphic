#include <iostream>
#include <string>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "shader.h"
#include "camera.h"

using namespace std;

void init();
void fillScene();

GLFWwindow* window;
int screenWidth = 1500;
int screenHeight = 900;
string title = "Potitle";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

bool keys[1024];
glm::vec2 mouseLastPosition(0.0f); 
glm::vec2 mouseDelta(0.0f); 

void updateOffsetPosition();
glm::vec3 offsetPosition;

Camera* camera;

int main()
{
    init();

    Shader shProxy = Shader("proxy.vert", "proxy.frag");

    fillScene();

    camera = new Camera(glm::vec3(-5.0f, 0.0f, 1.0f));

    GLint modelLoc = glGetUniformLocation(shProxy.Program, "model");
    GLint viewLoc = glGetUniformLocation(shProxy.Program, "view");
    GLint projLoc = glGetUniformLocation(shProxy.Program, "projection");

    glm::mat4 model = glm::mat4(1.f);
    glm::mat4 view = glm::mat4(1.f);
    glm::mat4 projection = glm::perspective(glm::radians(55.0f), (float)screenWidth/(float)screenHeight, 0.1f, 1000.0f);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        camera->update(offsetPosition, mouseDelta);

        glClearColor(0.91f, 0.85f, 0.73f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shProxy.use();

        for (int i_ill = 0; i_ill < 10; ++i_ill)
        {
            for (int j_ill = 0; j_ill < 10; ++j_ill)
            {
                for (int g_ill = 0; g_ill < 5; ++g_ill)
                {
                    model = glm::translate(glm::mat4(1.f), glm::vec3(i_ill * 10 - 50, j_ill * 10 - 50, g_ill * 20 - 40));
                    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                    glDrawArrays(GL_TRIANGLES, 0, 18);
                }
            }
        }

        view = camera->getViewMatrix();

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glfwSwapBuffers(window);
        
        mouseDelta = glm::vec2(0.0f);
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

    window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        throw runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    glViewport(0, 0, screenWidth, screenHeight);

    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw runtime_error("GLEW not init");
    }
}

void fillScene()
{
    GLfloat g_vertex_illuminati[] = {
        -0.5f,  -0.5f,  0.0f,   0.5f,   0.2f,   0.3f,
        0.0f,   0.0f,   0.6f,   0.5f,   0.2f,   0.3f,
        0.5f,   -0.5f,  0.0f,   0.5f,   0.2f,   0.3f,

        0.5f,   -0.5f,  0.0f,   0.9f,   0.6f,   0.3f,
        0.0f,   0.0f,   0.6f,   0.9f,   0.6f,   0.3f,
        0.5f,   0.5f,   0.0f,   0.9f,   0.6f,   0.3f,

        0.5f,   0.5f,   0.0f,   0.7f,   0.8f,   0.4f,
        0.0f,   0.0f,   0.6f,   0.7f,   0.8f,   0.4f,
        -0.5f,  0.5f,   0.0f,   0.7f,   0.8f,   0.4f,

        -0.5f,  0.5f,   0.0f,   0.3f,   0.6f,   0.4f,
        0.0f,   0.0f,   0.6f,   0.3f,   0.6f,   0.4f,
        -0.5f,  -0.5f,  0.0f,   0.3f,   0.6f,   0.4f,

        -0.5f,  -0.5f,  0.0f,   0.4f,   0.1f,   0.8f,
        0.5f,   -0.5f,  0.0f,   0.4f,   0.1f,   0.8f,
        0.5f,   0.5f,   0.0f,   0.4f,   0.1f,   0.8f,

        -0.5f,  -0.5f,  0.0f,   0.4f,   0.1f,   0.8f,
        -0.5f,  0.5f,   0.0f,   0.4f,   0.1f,   0.8f,
        0.5f,   0.5f,   0.0f,   0.4f,   0.1f,   0.8f,
    };

    GLuint VAO; 
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 

    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_illuminati), g_vertex_illuminati, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS) {
            keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            keys[key] = false;	
        }

        updateOffsetPosition();
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    glm::vec2 mouseNowPosition(xpos, ypos);

    if (mouseLastPosition == glm::vec2(0.f)) { // как установить курсор в нулевые координаты
        mouseLastPosition = mouseNowPosition;
    }

    mouseDelta = mouseNowPosition - mouseLastPosition;
    mouseLastPosition = mouseNowPosition;   
}

void updateOffsetPosition()
{
    offsetPosition = glm::vec3(
        (keys[GLFW_KEY_UP] || keys[GLFW_KEY_W]) - (keys[GLFW_KEY_DOWN] || keys[GLFW_KEY_S]), 
        (keys[GLFW_KEY_LEFT] || keys[GLFW_KEY_A]) - (keys[GLFW_KEY_RIGHT] || keys[GLFW_KEY_D]), 
        keys[GLFW_KEY_SPACE] - keys[GLFW_KEY_LEFT_CONTROL]
    );
}
