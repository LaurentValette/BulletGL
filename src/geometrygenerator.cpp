#include "geometrygenerator.h"

Cal::GeometryGenerator::GeometryGenerator(btDiscreteDynamicsWorld* dynamicsWorld, const int itemCount):
    m_dynamicsWorld(dynamicsWorld), geometryItems(itemCount), itemRotatingCounter(0), timestamp(0.0), timer(0.0),
    rng((std::random_device())()), distribution(0.f, 1.f)
{
    ObjLoader::parseObjFile("cube.obj", cube_vertices, cube_normals);
    ObjLoader::parseObjFile("cylinder.obj", cylinder_vertices, cylinder_normals);
    ObjLoader::parseObjFile("sphere.obj", sphere_vertices, sphere_normals);

    for (int i = 0; i < itemCount - 2; ++i)
    {
        addRandomGeometry(i);
    }
    geometryItems.at(itemCount - 2) = new Cal::Plane(dynamicsWorld);
    float radius = 0.2f;
    float length = 2.f;
    Cal::Cylinder* cy = new Cal::Cylinder(cylinder_vertices, cylinder_normals, dynamicsWorld, radius, length, btQuaternion(btVector3(0, 0, 1), glm::pi<float>() / 2.f), btVector3(length / 4.f, radius + 1, 0));
    geometryItems.at(itemCount - 1) = cy;
    // TODO: Just an experiment, do not leak references
    btHingeConstraint* constraint = new btHingeConstraint(cy->getRigidBody(), btVector3(0, 0, 0), btVector3(0, 0, 1));
    dynamicsWorld->addConstraint(constraint);
}

void Cal::GeometryGenerator::renderAll(const double deltaTime, GLuint program)
{
    timer += deltaTime;
    if (timer - timestamp >= 0.3f)
    {
        timestamp = timer;

        // Dispose of the oldest geometry item and pop a new one at a random position
        delete geometryItems[itemRotatingCounter];
        addRandomGeometry(itemRotatingCounter);
        itemRotatingCounter = (itemRotatingCounter + 1) % (geometryItems.size() - 2);
    }

    for (auto const& item : geometryItems)
    {
        item->render(program);
    }
}

float Cal::GeometryGenerator::randomFloat()
{
    return distribution(rng);
}

void Cal::GeometryGenerator::addRandomGeometry(int i)
{
    float rand = distribution(rng);
    if (rand < 0.33f)
    {
        // [0.5; 1.0[
        float cubeLength = distribution(rng) * 0.5f + 0.5f;
        geometryItems.at(i) = new Cal::Cube(cube_vertices, cube_normals, m_dynamicsWorld, cubeLength, btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0));
    }
    else if (rand < 0.66f)
    {
        // [0.25; 0.75[
        float cylinderRadius = distribution(rng) * 0.5f + 0.25f;
        // [0.75; 1.25[
        float cylinderLength = distribution(rng) * 0.5f + 0.75f;
        geometryItems.at(i) = new Cal::Cylinder(cylinder_vertices, cylinder_normals, m_dynamicsWorld, cylinderRadius, cylinderLength, btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0));
    }
    else
    {
        // [0.5; 0.75[
        float sphereRadius = distribution(rng) * 0.5f + 0.25f;
        geometryItems.at(i) = new Cal::Sphere(sphere_vertices, sphere_normals, m_dynamicsWorld, sphereRadius, btVector3(0, 10, 0));
    }
}

Cal::GeometryGenerator::~GeometryGenerator()
{
    geometryItems.clear();
}
