#include "plane.h"

Cal::Plane::Plane(btDiscreteDynamicsWorld* dynamicsWorld, const btVector3& normal, const float distance):
    Geometry(vertices, normals)
{
    m_dynamicsWorld = dynamicsWorld;

    collisionShape = new btStaticPlaneShape(normal, distance);
    motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
    btScalar mass = 0;
    btVector3 inertia(0, 0, 0);
    rigidBody = new btRigidBody(mass, motionState, collisionShape, inertia);
    dynamicsWorld->addRigidBody(rigidBody);
}

std::vector<glm::vec3> Cal::Plane::initPlaneVertices()
{
    std::vector<glm::vec3> v;

    v.push_back(glm::vec3(-10, 0, -10));
    v.push_back(glm::vec3(-10, 0, 10));
    v.push_back(glm::vec3(10, 0, -10));

    v.push_back(glm::vec3(-10, 0, 10));
    v.push_back(glm::vec3(10, 0, 10));
    v.push_back(glm::vec3(10, 0, -10));

    return v;
}

const std::vector<glm::vec3> Cal::Plane::vertices = initPlaneVertices();

std::vector<glm::vec3> Cal::Plane::initPlaneNormals()
{
    std::vector<glm::vec3> n;

    for (int i = 0; i < vertices.size(); ++i) {
        n.push_back(glm::vec3(0, 1, 0));
    }

    return n;
}

const std::vector<glm::vec3> Cal::Plane::normals = initPlaneNormals();

glm::mat4 Cal::Plane::getWorldTransform()
{
    btScalar model[16];
    rigidBody->getWorldTransform().getOpenGLMatrix(model);

    return glm::make_mat4(model);
}

Cal::Plane::~Plane()
{
}
