#include "plane.h"

Cal::Plane::Plane(btDiscreteDynamicsWorld* dynamicsWorld, const btVector3& normal, const float distance):
    m_dynamicsWorld(dynamicsWorld)
{
    collisionShape = new btStaticPlaneShape(normal, distance);
    motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
    btScalar mass = 0;
    btVector3 inertia(0, 0, 0);
    rigidBody = new btRigidBody(mass, motionState, collisionShape, inertia);
    dynamicsWorld->addRigidBody(rigidBody);

    // Create vertex array object
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    // Create vertex buffer
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat) * 3, vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void *)0);

    // Create normal buffer
    glGenBuffers(1, &normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat) * 3, normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, (void *)0);

    // Create index buffer
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint) * 3, indices.data(), GL_STATIC_DRAW);
}

std::vector<glm::vec3> initPlaneVertices()
{
    std::vector<glm::vec3> v;

    v.push_back(glm::vec3(-10, 0, -10));
    v.push_back(glm::vec3(-10, 0, 10));
    v.push_back(glm::vec3(10, 0, -10));
    v.push_back(glm::vec3(10, 0, 10));

    return v;
}

const std::vector<glm::vec3> Cal::Plane::vertices = initPlaneVertices();

std::vector<glm::vec3> initPlaneNormals()
{
    std::vector<glm::vec3> n;

    for (int i = 0; i < 4; ++i) {
        n.push_back(glm::vec3(0, 1, 0));
    }

    return n;
}

const std::vector<glm::vec3> Cal::Plane::normals = initPlaneNormals();

std::vector<glm::uvec3> initPlaneIndices()
{
    std::vector<glm::uvec3> i;

    i.push_back(glm::uvec3(0, 2, 1));
    i.push_back(glm::uvec3(1, 2, 3));

    return i;
}

const std::vector<glm::uvec3> Cal::Plane::indices = initPlaneIndices();

btRigidBody* Cal::Plane::getRigidBody()
{
    return rigidBody;
}

void Cal::Plane::getWorldTransform(glm::mat4& m)
{
    btScalar model[16];
    rigidBody->getWorldTransform().getOpenGLMatrix(model);

    m = glm::make_mat4(model);
}

void Cal::Plane::render(GLuint program)
{
    glm::mat4 model;
    getWorldTransform(model);
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, false, glm::value_ptr(model));
    glBindVertexArray(vertex_array_object);
    glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, (void*)0);
}

Cal::Plane::~Plane()
{
    m_dynamicsWorld->removeRigidBody(rigidBody);
    delete rigidBody;
    delete motionState;
    delete collisionShape;

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &normal_buffer);
    glDeleteBuffers(1, &index_buffer);
    glDeleteVertexArrays(1, &vertex_array_object);
}
