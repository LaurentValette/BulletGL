#include "plane.h"

Cal::Plane::Plane(const btVector3& normal, const float distance)
{
    collisionShape = new btStaticPlaneShape(normal, distance);
    motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
    btScalar mass = 0;
    btVector3 inertia(0, 0, 0);
    rigidBody = new btRigidBody(mass, motionState, collisionShape, inertia);

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

    // TODO: Change this to take the rotations into account
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

Cal::Plane::~Plane()
{
    delete rigidBody;
    delete motionState;
    delete collisionShape;

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &normal_buffer);
    glDeleteBuffers(1, &index_buffer);
}
