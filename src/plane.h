#ifndef CAL_PLANE_H
#define CAL_PLANE_H

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <btBulletDynamicsCommon.h>

#include <vector>

namespace Cal {
class Plane
{
public:
    Plane(const btVector3& normal = btVector3(0, 1, 0), const float distance = 0.f);
    btRigidBody* getRigidBody();
    void getWorldTransform(glm::mat4& m);
    ~Plane();

    static const std::vector<glm::vec3> vertices;
    static const std::vector<glm::vec3> normals;
    static const std::vector<glm::uvec3> indices;

private:
    btCollisionShape* collisionShape;
    btDefaultMotionState* motionState;
    btRigidBody* rigidBody;
    GLuint vertex_buffer;
    GLuint normal_buffer;
    GLuint index_buffer;
};
}

#endif // CAL_PLANE_H
