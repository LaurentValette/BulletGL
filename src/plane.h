#ifndef CAL_PLANE_H
#define CAL_PLANE_H

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <btBulletDynamicsCommon.h>

#include <vector>

#include "geometry.h"

namespace Cal {
class Plane: public Geometry
{
public:
    Plane(btDiscreteDynamicsWorld* dynamicsWorld, const btVector3& normal = btVector3(0, 1, 0), const float distance = 0.f);
    glm::mat4 getWorldTransform();
    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec3> getNormals();
    std::vector<glm::uvec3> getIndices();
    ~Plane();

    static std::vector<glm::vec3> initPlaneVertices();
    static std::vector<glm::vec3> initPlaneNormals();
    static std::vector<glm::uvec3> initPlaneIndices();

    static const std::vector<glm::vec3> vertices;
    static const std::vector<glm::vec3> normals;
    static const std::vector<glm::uvec3> indices;
};
}

#endif // CAL_PLANE_H
