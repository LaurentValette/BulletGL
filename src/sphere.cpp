#include "sphere.h"

Cal::Sphere::Sphere(btDiscreteDynamicsWorld* dynamicsWorld, const float radius, const btVector3& translation):
    Geometry(vertices, normals, indices), m_radius(radius)
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

std::vector<glm::vec3> Cal::Sphere::initSphereVertices()
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

const std::vector<glm::vec3> Cal::Sphere::vertices = Cal::Sphere::initSphereVertices();

std::vector<glm::vec3> Cal::Sphere::initSphereNormals()
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

const std::vector<glm::vec3> Cal::Sphere::normals = initSphereNormals();

std::vector<glm::uvec3> Cal::Sphere::initSphereIndices()
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

const std::vector<glm::uvec3> Cal::Sphere::indices = initSphereIndices();

std::vector<glm::vec3> Cal::Sphere::getVertices()
{
    return vertices;
}

std::vector<glm::vec3> Cal::Sphere::getNormals()
{
    return normals;
}

std::vector<glm::uvec3> Cal::Sphere::getIndices()
{
    return indices;
}

glm::mat4 Cal::Sphere::getWorldTransform()
{
    btScalar model[16];
    rigidBody->getWorldTransform().getOpenGLMatrix(model);

    return glm::scale(glm::make_mat4(model), glm::vec3(m_radius * 2.f));
}

Cal::Sphere::~Sphere()
{
}
