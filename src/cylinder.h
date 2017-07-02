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

namespace Cal {
class Cylinder
{
public:
    Cylinder(const float radius = 1.f, const float length = 3.f, const btQuaternion& rotation = btQuaternion(0, 0, 0, 1), const btVector3& translation = btVector3(0, 0, 0));
    btRigidBody* getRigidBody();
    void getWorldTransform(glm::mat4& m);
    ~Cylinder();

    static const std::vector<glm::vec3> vertices;
    static const std::vector<glm::vec3> normals;
    static const std::vector<glm::uvec3> indices;

private:
    float m_radius, m_length;
    btCollisionShape* collisionShape;
    btDefaultMotionState* motionState;
    btRigidBody* rigidBody;
    GLuint vertex_buffer;
    GLuint normal_buffer;
    GLuint index_buffer;
};
}

#endif // CAL_CYLINDER_H
