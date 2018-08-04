#ifndef CAL_CUBE_H
#define CAL_CUBE_H

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
class Cube: public Geometry
{
public:
    Cube(btDiscreteDynamicsWorld* dynamicsWorld, const float length = 1.f, const btQuaternion& rotation = btQuaternion(0, 0, 0, 1), const btVector3& translation = btVector3(0, 0, 0));
    glm::mat4 getWorldTransform();
    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec3> getNormals();
    std::vector<glm::uvec3> getIndices();
    ~Cube();

    static std::vector<glm::vec3> initCubeVertices();
    static std::vector<glm::vec3> initCubeNormals();
    static std::vector<glm::uvec3> initCubeIndices();

    static const std::vector<glm::vec3> vertices;
    static const std::vector<glm::vec3> normals;
    static const std::vector<glm::uvec3> indices;

private:
    float m_length;
};
}

#endif // CAL_CUBE_H
