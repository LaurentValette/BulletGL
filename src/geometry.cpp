#include "geometry.h"

Cal::Geometry::Geometry()
{
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
