#include "cube.h"

Cal::Cube::Cube(btDiscreteDynamicsWorld* dynamicsWorld, const float length, const btQuaternion& rotation, const btVector3& translation):
    scale(length)
{
    m_dynamicsWorld = dynamicsWorld;

    collisionShape = new btBoxShape(btVector3(length / 2.f, length / 2.f, length / 2.f));
    motionState = new btDefaultMotionState(btTransform(rotation, translation));
    btScalar mass = 1;
    btVector3 inertia(0, 0, 0);
    collisionShape->calculateLocalInertia(mass, inertia);
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

std::vector<glm::vec3> initCubeVertices()
{
    std::vector<glm::vec3> v;

    v.push_back(glm::vec3(-0.5, -0.5, 0.5));
    v.push_back(glm::vec3(0.5, -0.5, 0.5));
    v.push_back(glm::vec3(-0.5, 0.5, 0.5));
    v.push_back(glm::vec3(0.5, 0.5, 0.5));

    v.push_back(glm::vec3(0.5, -0.5, 0.5));
    v.push_back(glm::vec3(0.5, -0.5, -0.5));
    v.push_back(glm::vec3(0.5, 0.5, 0.5));
    v.push_back(glm::vec3(0.5, 0.5, -0.5));

    v.push_back(glm::vec3(0.5, -0.5, -0.5));
    v.push_back(glm::vec3(-0.5, -0.5, -0.5));
    v.push_back(glm::vec3(0.5, 0.5, -0.5));
    v.push_back(glm::vec3(-0.5, 0.5, -0.5));

    v.push_back(glm::vec3(-0.5, -0.5, -0.5));
    v.push_back(glm::vec3(-0.5, -0.5, 0.5));
    v.push_back(glm::vec3(-0.5, 0.5, -0.5));
    v.push_back(glm::vec3(-0.5, 0.5, 0.5));

    v.push_back(glm::vec3(-0.5, -0.5, -0.5));
    v.push_back(glm::vec3(0.5, -0.5, -0.5));
    v.push_back(glm::vec3(-0.5, -0.5, 0.5));
    v.push_back(glm::vec3(0.5, -0.5, 0.5));

    v.push_back(glm::vec3(-0.5, 0.5, 0.5));
    v.push_back(glm::vec3(0.5, 0.5, 0.5));
    v.push_back(glm::vec3(-0.5, 0.5, -0.5));
    v.push_back(glm::vec3(0.5, 0.5, -0.5));

    return v;
}

const std::vector<glm::vec3> Cal::Cube::vertices = initCubeVertices();

std::vector<glm::vec3> initCubeNormals()
{
    std::vector<glm::vec3> n;

    for (int i = 0; i < 4; ++i) {
        n.push_back(glm::vec3(0, 0, 1));
    }

    for (int i = 0; i < 4; ++i) {
        n.push_back(glm::vec3(1, 0, 0));
    }

    for (int i = 0; i < 4; ++i) {
        n.push_back(glm::vec3(0, 0, -1));
    }

    for (int i = 0; i < 4; ++i) {
        n.push_back(glm::vec3(-1, 0, 0));
    }

    for (int i = 0; i < 4; ++i) {
        n.push_back(glm::vec3(0, -1, 0));
    }

    for (int i = 0; i < 4; ++i) {
        n.push_back(glm::vec3(0, 1, 0));
    }

    return n;
}

const std::vector<glm::vec3> Cal::Cube::normals = initCubeNormals();

std::vector<glm::uvec3> initCubeIndices()
{
    std::vector<glm::uvec3> i;

    i.push_back(glm::uvec3(0, 2, 1));
    i.push_back(glm::uvec3(1, 2, 3));

    i.push_back(glm::uvec3(4, 7, 5));
    i.push_back(glm::uvec3(4, 6, 7));

    i.push_back(glm::uvec3(8, 11, 9));
    i.push_back(glm::uvec3(8, 10, 11));

    i.push_back(glm::uvec3(12, 14, 13));
    i.push_back(glm::uvec3(13, 14, 15));

    i.push_back(glm::uvec3(16, 18, 17));
    i.push_back(glm::uvec3(17, 18, 19));

    i.push_back(glm::uvec3(20, 23, 21));
    i.push_back(glm::uvec3(20, 22, 23));

    return i;
}

const std::vector<glm::uvec3> Cal::Cube::indices = initCubeIndices();

std::vector<glm::vec3> Cal::Cube::getVertices()
{
    return vertices;
}

std::vector<glm::vec3> Cal::Cube::getNormals()
{
    return normals;
}

std::vector<glm::uvec3> Cal::Cube::getIndices()
{
    return indices;
}

glm::mat4 Cal::Cube::getWorldTransform()
{
    btScalar model[16];
    rigidBody->getWorldTransform().getOpenGLMatrix(model);

    return glm::scale(glm::make_mat4(model), glm::vec3(scale));
}

Cal::Cube::~Cube()
{
}
