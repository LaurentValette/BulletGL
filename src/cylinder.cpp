#include "cylinder.h"

Cal::Cylinder::Cylinder(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals,
                        btDiscreteDynamicsWorld* dynamicsWorld, const float radius, const float length, const btQuaternion& rotation, const btVector3& translation):
    Geometry(vertices, normals), m_radius(radius), m_length(length)
{
    m_dynamicsWorld = dynamicsWorld;

    collisionShape = new btCylinderShape(btVector3(radius, length / 2.f, radius));
    motionState = new btDefaultMotionState(btTransform(rotation, translation));
    float volume = glm::pi<float>() * radius * radius * length;
    btScalar mass = volume;
    btVector3 inertia(0, 0, 0);
    collisionShape->calculateLocalInertia(mass, inertia);
    rigidBody = new btRigidBody(mass, motionState, collisionShape, inertia);
    m_dynamicsWorld->addRigidBody(rigidBody);
}

glm::mat4 Cal::Cylinder::getWorldTransform()
{
    btScalar model[16];
    rigidBody->getWorldTransform().getOpenGLMatrix(model);

    return glm::scale(glm::make_mat4(model), glm::vec3(m_radius, m_length, m_radius));
}

btRigidBody& Cal::Cylinder::getRigidBody()
{
    return *rigidBody;
}

Cal::Cylinder::~Cylinder()
{
}
