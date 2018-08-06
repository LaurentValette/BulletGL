#include "sphere.h"

Cal::Sphere::Sphere(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals,
                    btDiscreteDynamicsWorld* dynamicsWorld, const float radius, const btVector3& translation):
    Geometry(vertices, normals), m_radius(radius)
{
    m_dynamicsWorld = dynamicsWorld;

    collisionShape = new btSphereShape(radius);
    motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), translation));
    float volume = 4.f / 3.f * glm::pi<float>() * radius * radius * radius;
    btScalar mass = volume;
    btVector3 inertia(0, 0, 0);
    collisionShape->calculateLocalInertia(mass, inertia);
    rigidBody = new btRigidBody(mass, motionState, collisionShape, inertia);
    dynamicsWorld->addRigidBody(rigidBody);
}

glm::mat4 Cal::Sphere::getWorldTransform()
{
    btScalar model[16];
    rigidBody->getWorldTransform().getOpenGLMatrix(model);

    return glm::scale(glm::make_mat4(model), glm::vec3(m_radius));
}

Cal::Sphere::~Sphere()
{
}
