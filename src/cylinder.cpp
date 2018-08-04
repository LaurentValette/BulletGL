#include "cylinder.h"

#define CYLINDER_PERIMETER 20
#define CYLINDER_HEIGHT 2

Cal::Cylinder::Cylinder(btDiscreteDynamicsWorld* dynamicsWorld, const float radius, const float length, const btQuaternion& rotation, const btVector3& translation):
    Geometry(vertices, normals, indices), m_radius(radius), m_length(length)
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

std::vector<glm::vec3> Cal::Cylinder::initCylinderVertices()
{
    std::vector<glm::vec3> v;

    // Sides
    float y = -0.5f;
    for (int height = 0; height < CYLINDER_HEIGHT; ++height) {
        float theta = 0.f;
        for (int i = 0; i < CYLINDER_PERIMETER; ++i) {
            v.push_back(glm::vec3(glm::cos(theta), y, glm::sin(theta)));
            theta += 2.f * glm::pi<float>() / CYLINDER_PERIMETER;
        }
        y += 1.f / (CYLINDER_HEIGHT - 1);
    }

    // Bottom
    v.push_back(glm::vec3(0.f, -0.5f, 0.f));
    float theta = 0.f;
    for (int i = 0; i < CYLINDER_PERIMETER; ++i) {
        v.push_back(glm::vec3(glm::cos(theta), -0.5f, glm::sin(theta)));
        theta += 2.f * glm::pi<float>() / CYLINDER_PERIMETER;
    }

    // Top
    v.push_back(glm::vec3(0.f, 0.5f, 0.f));
    theta = 0.f;
    for (int i = 0; i < CYLINDER_PERIMETER; ++i) {
        v.push_back(glm::vec3(glm::cos(theta), 0.5f, glm::sin(theta)));
        theta += 2.f * glm::pi<float>() / CYLINDER_PERIMETER;
    }

    return v;
}

const std::vector<glm::vec3> Cal::Cylinder::vertices = initCylinderVertices();

std::vector<glm::vec3> Cal::Cylinder::initCylinderNormals()
{
    std::vector<glm::vec3> n;

    // Sides
    for (int y = 0; y < CYLINDER_HEIGHT; ++y) {
        float theta = 0.f;
        for (int i = 0; i < CYLINDER_PERIMETER; ++i) {
            n.push_back(glm::vec3(glm::cos(theta), 0.f, glm::sin(theta)));
            theta += 2.f * glm::pi<float>() / CYLINDER_PERIMETER;
        }
    }

    // Bottom
    for (int i = 0; i <= CYLINDER_PERIMETER; ++i) {
        n.push_back(glm::vec3(0.f, -1.f, 0.f));
    }

    // Top
    for (int i = 0; i <= CYLINDER_PERIMETER; ++i) {
        n.push_back(glm::vec3(0.f, 1.f, 0.f));
    }

    return n;
}

const std::vector<glm::vec3> Cal::Cylinder::normals = initCylinderNormals();

std::vector<glm::uvec3> Cal::Cylinder::initCylinderIndices()
{
    std::vector<glm::uvec3> indices;

    // Sides
    for (int y = 0; y < CYLINDER_HEIGHT - 1; ++y) {
        for (int i = 0; i < CYLINDER_PERIMETER; ++i) {
            indices.push_back(glm::uvec3(CYLINDER_PERIMETER * y + i,
                                         CYLINDER_PERIMETER * y + ((i + 1) % CYLINDER_PERIMETER),
                                         CYLINDER_PERIMETER * (y + 1) + i));
            indices.push_back(glm::uvec3(CYLINDER_PERIMETER * y + ((i + 1) % CYLINDER_PERIMETER),
                                         CYLINDER_PERIMETER * (y + 1) + ((i + 1) % CYLINDER_PERIMETER),
                                         CYLINDER_PERIMETER * (y + 1) + i));
        }
    }

    // Bottom
    int center_index = CYLINDER_HEIGHT * CYLINDER_PERIMETER + 1;
    for (int i = 0; i < CYLINDER_PERIMETER; ++i) {
        indices.push_back(glm::uvec3(center_index - 1, center_index + ((i + 1) % CYLINDER_PERIMETER), center_index + i));
    }

    // Top
    center_index = (CYLINDER_HEIGHT + 1) * CYLINDER_PERIMETER + 2;
    for (int i = 0; i < CYLINDER_PERIMETER; ++i) {
        indices.push_back(glm::uvec3(center_index - 1, center_index + i, center_index + ((i + 1) % CYLINDER_PERIMETER)));
    }

    return indices;
}

const std::vector<glm::uvec3> Cal::Cylinder::indices = initCylinderIndices();

std::vector<glm::vec3> Cal::Cylinder::getVertices()
{
    return vertices;
}

std::vector<glm::vec3> Cal::Cylinder::getNormals()
{
    return normals;
}

std::vector<glm::uvec3> Cal::Cylinder::getIndices()
{
    return indices;
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
