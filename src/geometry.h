#ifndef CAL_GEOMETRY_H
#define CAL_GEOMETRY_H

#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <btBulletDynamicsCommon.h>

namespace Cal {
class Geometry
{
public:
    Geometry(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals);
    virtual glm::mat4 getWorldTransform() = 0;
    virtual void render(GLuint program);
    virtual ~Geometry();

protected:
    btDiscreteDynamicsWorld* m_dynamicsWorld;
    btCollisionShape* collisionShape;
    btDefaultMotionState* motionState;
    btRigidBody* rigidBody;
    GLuint vertex_buffer;
    GLuint normal_buffer;
    GLuint vertex_array_object;

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
};
}


#endif // CAL_GEOMETRY_H
