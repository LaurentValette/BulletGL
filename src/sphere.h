#ifndef CAL_SPHERE_H
#define CAL_SPHERE_H

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
class Sphere: public Geometry
{
public:
    Sphere(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals,
           btDiscreteDynamicsWorld* dynamicsWorld, const float radius = 1.f, const btVector3& translation = btVector3(0, 0, 0));
    glm::mat4 getWorldTransform();
    ~Sphere();

private:
    float m_radius;
};
}
#endif // CAL_SPHERE_H
