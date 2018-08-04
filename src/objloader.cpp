#include "objloader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

bool ObjLoader::parseObjFile(const char* filePath, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filePath);

    if (!err.empty()) {
        std::cerr << err << std::endl;
        return false;
    }

    if (!ret) {
        std::cerr << "load obj returned false" << std::endl;
        return false;
    }

    tinyobj::shape_t shape = shapes[0];
    size_t index_offset = 0;
    for (size_t faceIndex = 0; faceIndex < shape.mesh.num_face_vertices.size(); faceIndex++) {
        const int fv = 3;

        for (size_t ve = 0; ve < fv; ve++) {
            tinyobj::index_t vertex = shape.mesh.indices[index_offset + ve];

            tinyobj::real_t vx = attrib.vertices[3 * vertex.vertex_index + 0];
            tinyobj::real_t vy = attrib.vertices[3 * vertex.vertex_index + 1];
            tinyobj::real_t vz = attrib.vertices[3 * vertex.vertex_index + 2];
            vertices.push_back(glm::vec3(vx, vy, vz));

            tinyobj::real_t nx = attrib.normals[3 * vertex.normal_index + 0];
            tinyobj::real_t ny = attrib.normals[3 * vertex.normal_index + 1];
            tinyobj::real_t nz = attrib.normals[3 * vertex.normal_index + 2];

            normals.push_back(glm::vec3(nx, ny, nz));
        }

        index_offset += fv;
    }

    return true;
}
