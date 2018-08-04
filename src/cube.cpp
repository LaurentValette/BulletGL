#include "cube.h"

Cal::Cube::Cube(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
                btDiscreteDynamicsWorld* dynamicsWorld, const float length, const btQuaternion& rotation, const btVector3& translation):
    Geometry(vertices, normals), m_length(length), m_vertices(vertices), m_normals(normals)
{
    m_dynamicsWorld = dynamicsWorld;

    collisionShape = new btBoxShape(btVector3(length / 2.f, length / 2.f, length / 2.f));
    motionState = new btDefaultMotionState(btTransform(rotation, translation));
    btScalar mass = 1;
    btVector3 inertia(0, 0, 0);
    collisionShape->calculateLocalInertia(mass, inertia);
    rigidBody = new btRigidBody(mass, motionState, collisionShape, inertia);
    dynamicsWorld->addRigidBody(rigidBody);
}

std::vector<glm::vec3> Cal::Cube::getVertices()
{
    return m_vertices;
}

std::vector<glm::vec3> Cal::Cube::getNormals()
{
    return m_normals;
}

glm::mat4 Cal::Cube::getWorldTransform()
{
    btScalar model[16];
    rigidBody->getWorldTransform().getOpenGLMatrix(model);

    return glm::scale(glm::make_mat4(model), glm::vec3(m_length));
}

Cal::Cube::~Cube()
{
}
