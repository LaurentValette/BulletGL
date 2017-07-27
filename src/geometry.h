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
    Geometry(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::uvec3> indices);
    virtual glm::mat4 getWorldTransform() = 0;
    virtual void render(GLuint program);
    virtual std::vector<glm::vec3> getVertices() = 0;
    virtual std::vector<glm::vec3> getNormals() = 0;
    virtual std::vector<glm::uvec3> getIndices() = 0;
    virtual ~Geometry();

protected:
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


#endif // CAL_GEOMETRY_H
