#include <iostream>
#include <chrono>
#include <thread>

#include <btBulletDynamicsCommon.h>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "shaderloader.h"
#include "geometrygenerator.h"

#define WIDTH 1280
#define HEIGHT 768
#define MULTISAMPLING 16

int main(int argc, char** argv) {
    // Create Bullet context
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    // Create OpenGL context
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  #if MULTISAMPLING
    glfwWindowHint(GLFW_SAMPLES, MULTISAMPLING);
  #endif
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Demo", NULL, NULL);
    glfwMakeContextCurrent(window);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glewExperimental = GL_TRUE;
    glewInit();

    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    Cal::GeometryGenerator* geometryGenerator = new Cal::GeometryGenerator(dynamicsWorld, 100);

    // Create shader
    GLuint program = glCreateProgram();

    ShaderLoader::attachShader("shader.vert", GL_VERTEX_SHADER, program);
    ShaderLoader::attachShader("shader.frag", GL_FRAGMENT_SHADER, program);
    glLinkProgram(program);

    // Configure rendering
  #if MULTISAMPLING
    glEnable(GL_MULTISAMPLE);
  #endif
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glUseProgram(program);
    // Create the perspective projection matrix and the model view matrix
    glm::mat4 projection = glm::perspective(45.f, ((float) width) / height, 0.1f, 10.f);
    glm::mat4 view = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    float theta = 0;

    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, false, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, false, glm::value_ptr(view));

    // Create a framebuffer for the shadowmap
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);

    double deltaTime = 1.0 / 60.0;
    int frameCount = 0;
    double timer = 0.0;

    do
    {
        // Step bullet simulation
        double startTime = glfwGetTime();
        dynamicsWorld->stepSimulation(deltaTime, 1);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set the light position
        theta += glm::pi<float>() / 2.f * deltaTime;
        glm::vec3 light_pos(2.f * glm::cos(theta), 1.5f, 2.f * glm::sin(theta));
        glUniform3fv(glGetUniformLocation(program, "light_pos"), 1, glm::value_ptr(light_pos));

        geometryGenerator->renderAll(deltaTime, program);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // FPS counter
        ++frameCount;
        if (timer >= 1.0)
        {
            std::cout << frameCount << std::endl;
            frameCount = 0;
            timer = 0.0;
        }

        // Frame limiter
        if (!glfwGetWindowAttrib(window, GLFW_FOCUSED))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((int) (30.0 - deltaTime)));
        }

        deltaTime = glfwGetTime() - startTime;
        timer += deltaTime;
    } while (!glfwWindowShouldClose(window));

    delete geometryGenerator;

    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();

    delete dynamicsWorld;
    delete solver;
    delete collisionConfiguration;
    delete dispatcher;
    delete broadphase;

    return 0;
}
