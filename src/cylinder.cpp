#include "cylinder.h"

Cal::Cylinder::Cylinder(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
                        btDiscreteDynamicsWorld* dynamicsWorld, const float radius, const float length, const btQuaternion& rotation, const btVector3& translation):
    Geometry(vertices, normals), m_radius(radius), m_length(length), m_vertices(vertices), m_normals(normals)
{
    m_dynamicsWorld = dynamicsWorld;

    collisionShape = new btCylinderShape(btVector3(radius, length / 2.f, radius));
    motionState = new btDefaultMotionState(btTransform(rotation, translation));
    btScalar mass = 1;
    btVector3 inertia(0, 0, 0);
    collisionShape->calculateLocalInertia(mass, inertia);
    rigidBody = new btRigidBody(mass, motionState, collisionShape, inertia);
    m_dynamicsWorld->addRigidBody(rigidBody);
}

std::vector<glm::vec3> Cal::Cylinder::getVertices()
{
    return m_vertices;
}

std::vector<glm::vec3> Cal::Cylinder::getNormals()
{
    return m_normals;
}

glm::mat4 Cal::Cylinder::getWorldTransform()
{
    btScalar model[16];
    rigidBody->getWorldTransform().getOpenGLMatrix(model);

    return glm::scale(glm::make_mat4(model), glm::vec3(m_radius, m_length, m_radius));
}

Cal::Cylinder::~Cylinder()
{
}
