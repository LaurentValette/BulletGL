#ifndef CAL_OBJLOADER_H
#define CAL_OBJLOADER_H

#include <iostream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace ObjLoader
{
    bool parseObjFile(const char* filePath, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals);
}

#endif // CAL_OBJLOADER_H
