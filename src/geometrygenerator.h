#ifndef CAL_GEOMETRYGENERATOR_H
#define CAL_GEOMETRYGENERATOR_H

#include <vector>
#include <random>
#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "geometry.h"
#include "cube.h"
#include "cylinder.h"
#include "plane.h"
#include "sphere.h"

#include "objloader.h"

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

    std::vector<glm::vec3> cube_vertices;
    std::vector<glm::vec3> cube_normals;
    std::vector<glm::vec3> cylinder_vertices;
    std::vector<glm::vec3> cylinder_normals;
    std::vector<glm::vec3> sphere_vertices;
    std::vector<glm::vec3> sphere_normals;
};
}


#endif // CAL_GEOMETRYGENERATOR_H
