#include "geometrygenerator.h"

Cal::GeometryGenerator::GeometryGenerator(btDiscreteDynamicsWorld* dynamicsWorld, const int itemCount):
    m_dynamicsWorld(dynamicsWorld), geometryItems(itemCount + 1), itemRotatingCounter(0), timestamp(0.0), timer(0.0),
    rng((std::random_device())()), distribution(0.f, 1.f)
{
    for (int i = 0; i < itemCount; ++i)
    {
        addRandomGeometry(i);
    }
    geometryItems.at(itemCount) = std::unique_ptr<Cal::Geometry>(new Cal::Plane(dynamicsWorld));
}

void Cal::GeometryGenerator::renderAll(const double deltaTime, GLuint program)
{
    timer += deltaTime;
    if (timer - timestamp >= 0.3f)
    {
        timestamp = timer;

        // Dispose of the oldest geometry item and pop a new one at a random position
        addRandomGeometry(itemRotatingCounter);
        itemRotatingCounter = (itemRotatingCounter + 1) % (geometryItems.size() - 1);
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
    if (distribution(rng) < 0.5f)
    {
        // [0.5; 1.0[
        float cubeLength = distribution(rng) * 0.5f + 0.5f;
        geometryItems.at(i) = std::unique_ptr<Cal::Geometry>(new Cal::Cube(m_dynamicsWorld, cubeLength, btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));
    }
    else
    {
        // [0.25; 0.75[
        float cylinderRadius = distribution(rng) * 0.5f + 0.25f;
        // [0.75; 1.25[
        float cylinderLength = distribution(rng) * 0.5f + 0.75f;
        geometryItems.at(i) = std::unique_ptr<Cal::Geometry>(new Cal::Cylinder(m_dynamicsWorld, cylinderRadius, cylinderLength, btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));
    }
}
