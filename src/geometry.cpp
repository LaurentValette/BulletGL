#include "geometry.h"

Cal::Geometry::Geometry(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::uvec3> indices)
{
    // Create vertex array object
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    // Create vertex buffer
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat) * 3, vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void *)0);

    // Create normal buffer
    glGenBuffers(1, &normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat) * 3, normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, (void *)0);

    // Create index buffer
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint) * 3, indices.data(), GL_STATIC_DRAW);
}

void Cal::Geometry::render(GLuint program)
{
    glm::mat4 model = getWorldTransform();
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, false, glm::value_ptr(model));
    glBindVertexArray(vertex_array_object);
    glDrawElements(GL_TRIANGLES, getIndices().size() * 3, GL_UNSIGNED_INT, (void*)0);
}

Cal::Geometry::~Geometry()
{
    m_dynamicsWorld->removeRigidBody(rigidBody);
    delete rigidBody;
    delete motionState;
    delete collisionShape;

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &normal_buffer);
    glDeleteBuffers(1, &index_buffer);
    glDeleteVertexArrays(1, &vertex_array_object);
}
