#include "sphere.h"

Cal::Sphere::Sphere(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
                    btDiscreteDynamicsWorld* dynamicsWorld, const float radius, const btVector3& translation):
    Geometry(vertices, normals), m_radius(radius), m_vertices(vertices), m_normals(normals)
{
    m_dynamicsWorld = dynamicsWorld;

    collisionShape = new btSphereShape(radius);
    motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), translation));
    btScalar mass = 1;
    btVector3 inertia(0, 0, 0);
    collisionShape->calculateLocalInertia(mass, inertia);
    rigidBody = new btRigidBody(mass, motionState, collisionShape, inertia);
    dynamicsWorld->addRigidBody(rigidBody);
}

std::vector<glm::vec3> Cal::Sphere::getVertices()
{
    return m_vertices;
}

std::vector<glm::vec3> Cal::Sphere::getNormals()
{
    return m_normals;
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
