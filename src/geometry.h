#ifndef CAL_GEOMETRY_H
#define CAL_GEOMETRY_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <btBulletDynamicsCommon.h>

namespace Cal {
class Geometry
{
public:
    Geometry();
    virtual btRigidBody* getRigidBody() = 0;
    virtual void getWorldTransform(glm::mat4& m) = 0;
    virtual ~Geometry();
};
}


#endif // CAL_GEOMETRY_H
