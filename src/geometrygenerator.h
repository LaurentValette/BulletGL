#ifndef CAL_GEOMETRYGENERATOR_H
#define CAL_GEOMETRYGENERATOR_H

#include <vector>
#include <random>
#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>

#include "geometry.h"
#include "cube.h"
#include "cylinder.h"
#include "plane.h"

namespace Cal {
class GeometryGenerator
{
public:
    GeometryGenerator(btDiscreteDynamicsWorld* dynamicsWorld, const int itemCount = 10);
    void renderAll(const double deltaTime, GLuint program);
    ~GeometryGenerator();

private:
    float randomFloat();
    void addRandomGeometry(int index);

    btDiscreteDynamicsWorld* m_dynamicsWorld;
    std::vector<std::unique_ptr<Cal::Geometry>> geometryItems;
    int itemRotatingCounter;

    double timestamp;
    double timer;

    std::mt19937 rng;
    std::uniform_real_distribution<float> distribution;
};
}


#endif // CAL_GEOMETRYGENERATOR_H
