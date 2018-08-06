#include "cube.h"

Cal::Cube::Cube(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals,
                btDiscreteDynamicsWorld* dynamicsWorld, const float length, const btQuaternion& rotation, const btVector3& translation):
    Geometry(vertices, normals), m_length(length)
{
    m_dynamicsWorld = dynamicsWorld;

    collisionShape = new btBoxShape(btVector3(length / 2.f, length / 2.f, length / 2.f));
    motionState = new btDefaultMotionState(btTransform(rotation, translation));
    float volume = length * length * length;
    btScalar mass = volume;
    btVector3 inertia(0, 0, 0);
    collisionShape->calculateLocalInertia(mass, inertia);
    rigidBody = new btRigidBody(mass, motionState, collisionShape, inertia);
    dynamicsWorld->addRigidBody(rigidBody);
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
