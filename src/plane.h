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
    btRigidBody* getRigidBody();
    void getWorldTransform(glm::mat4& m);
    void render(GLuint program);
    ~Plane();

    static const std::vector<glm::vec3> vertices;
    static const std::vector<glm::vec3> normals;
    static const std::vector<glm::uvec3> indices;

private:
    btDiscreteDynamicsWorld* m_dynamicsWorld;
    btCollisionShape* collisionShape;
    btDefaultMotionState* motionState;
    btRigidBody* rigidBody;
    GLuint vertex_buffer;
    GLuint normal_buffer;
    GLuint index_buffer;
    GLuint vertex_array_object;
};
}

#endif // CAL_PLANE_H
