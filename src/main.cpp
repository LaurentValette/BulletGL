#include <iostream>

#include <btBulletDynamicsCommon.h>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "cube.h"
#include "plane.h"
#include "cylinder.h"

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
    GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "Demo", NULL, NULL);
    glfwMakeContextCurrent(window);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glewExperimental = GL_TRUE;
    glewInit();

    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    GLuint ground_vao;
    glGenVertexArrays(1, &ground_vao);
    glBindVertexArray(ground_vao);
    Cal::Plane* ground = new Cal::Plane();
    dynamicsWorld->addRigidBody(ground->getRigidBody());

    GLuint cube_vao;
    glGenVertexArrays(1, &cube_vao);
    glBindVertexArray(cube_vao);
    Cal::Cube* cube = new Cal::Cube(1.0, btQuaternion(0, 0, 0, 1), btVector3(0, 1, 0));
    dynamicsWorld->addRigidBody(cube->getRigidBody());

    GLuint cylinder_vao;
    glGenVertexArrays(1, &cylinder_vao);
    glBindVertexArray(cylinder_vao);
    Cal::Cylinder* cylinder = new Cal::Cylinder(0.5f, 1.f, btQuaternion(0, 0, 0, 1), btVector3(0.f, 3.f, 0.f));
    dynamicsWorld->addRigidBody(cylinder->getRigidBody());

    // Create shader
    char const * vsrc = "\
      #version 330 core                                                           \n\
      layout(location = 0) in vec3 position;                                      \n\
      layout(location = 1) in vec3 normal;                                        \n\
      out vec3 light_dir, nor;                                                    \n\
      uniform mat4 model, view, projection;                                       \n\
      uniform vec3 light_pos;                                                     \n\
      void main() {                                                               \n\
        vec4 vertex_mv = view * model * vec4(position, 1.0);                      \n\
        gl_Position = projection * vertex_mv;                                     \n\
        nor = (transpose(inverse(view * model)) * vec4(normal, 0.0)).xyz;         \n\
        light_dir = (view * vec4(light_pos, 1.0)).xyz - vertex_mv.xyz;            \n\
      }                                                                           \n\
    ";
    char const * fsrc = "\
      #version 330                                                                \n\
      in vec3 light_dir, nor;                                                     \n\
      out vec4 color;                                                             \n\
      void main() {                                                               \n\
        float d = max(dot(normalize(nor), normalize(light_dir)), 0.f);            \n\
        color = vec4(d, d, d, 1.0);                                               \n\
      }                                                                           \n\
    ";
    GLuint program = glCreateProgram();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsrc, NULL);
    glCompileShader(vs);
    glAttachShader(program, vs);
    glDeleteShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsrc, NULL);
    glCompileShader(fs);
    glAttachShader(program, fs);
    glDeleteShader(fs);
    glLinkProgram(program);

    // Configure rendering
  #if MULTISAMPLING
    glEnable(GL_MULTISAMPLE);
  #endif
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glUseProgram(program);
    // Create the perspective projection matrix and the model view matrix
    glm::mat4 projection = glm::perspective(45.f, ((float) width) / height, 0.1f, 10.f);
    glm::mat4 view = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model;
    float theta = 0;

    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, false, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, false, glm::value_ptr(view));

    double deltaTime = 1.f / 60.f;

    do {
        double startTime = glfwGetTime();
        dynamicsWorld->stepSimulation(deltaTime, 1);

        cube->getWorldTransform(model);
        glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, false, glm::value_ptr(model));

        theta += glm::pi<float>() / 2.f * deltaTime;
        glm::vec3 light_pos(2.f * glm::cos(theta), 1.5f, 2.f * glm::sin(theta));
        glUniform3fv(glGetUniformLocation(program, "light_pos"), 1, glm::value_ptr(light_pos));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(cube_vao);
        glDrawElements(GL_TRIANGLES, cube->indices.size() * 3, GL_UNSIGNED_INT, (void*)0);

        glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, false, glm::value_ptr(glm::mat4()));
        glBindVertexArray(ground_vao);
        glDrawElements(GL_TRIANGLES, ground->indices.size() * 3, GL_UNSIGNED_INT, (void*)0);

        cylinder->getWorldTransform(model);
        glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, false, glm::value_ptr(model));
        glBindVertexArray(cylinder_vao);
        glDrawElements(GL_TRIANGLES, cylinder->indices.size() * 3, GL_UNSIGNED_INT, (void*)0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        deltaTime = glfwGetTime() - startTime;
    } while (!glfwWindowShouldClose(window));

    dynamicsWorld->removeRigidBody(ground->getRigidBody());
    dynamicsWorld->removeRigidBody(cube->getRigidBody());
    dynamicsWorld->removeRigidBody(cylinder->getRigidBody());
    delete ground;
    delete cube;
    delete cylinder;

    glDeleteVertexArrays(1, &ground_vao);
    glDeleteVertexArrays(1, &cube_vao);
    glDeleteVertexArrays(1, &cylinder_vao);
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