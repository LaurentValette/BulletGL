#ifndef CAL_CYLINDER_H
#define CAL_CYLINDER_H

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
class Cylinder: public Geometry
{
public:
    Cylinder(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals,
             btDiscreteDynamicsWorld* dynamicsWorld, const float radius = 1.f, const float length = 3.f, const btQuaternion& rotation = btQuaternion(0, 0, 0, 1), const btVector3& translation = btVector3(0, 0, 0));
    glm::mat4 getWorldTransform();
    btRigidBody& getRigidBody();

    ~Cylinder();

private:
    float m_radius, m_length;
};
}

#endif // CAL_CYLINDER_H
