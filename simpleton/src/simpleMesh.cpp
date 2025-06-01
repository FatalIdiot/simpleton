#include "simpleMesh.hpp"

#include "glad/glad.h"
#include <iostream>

namespace Simpleton {
    SimpleMesh::SimpleMesh(float* vertices, int vertSize, int* indices, int indSize) {
        m_vertSize = vertSize;
        m_indSize = indSize;

        glGenVertexArrays(1, &m_VAO);
        std::cout << "Generated VAO: " << m_VAO << std::endl;
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_VBO);
        std::cout << "Generated VBO: " << m_VBO << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glGenBuffers(1, &m_EBO);
        std::cout << "Generated EBO: " << m_EBO << std::endl;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertSize, vertices, GL_STATIC_DRAW);
        std::cout << "Size of added vertices: " << sizeof(float) * vertSize << std::endl;

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indSize, indices, GL_STATIC_DRAW);
        std::cout << "Size of added indices: " << sizeof(int) * indSize << std::endl;

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void SimpleMesh::Terminate() {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    void SimpleMesh::Draw() {
        Bind();

        glDrawElements(GL_TRIANGLES, m_indSize, GL_UNSIGNED_INT, 0);

        Unbind();
    }

    void SimpleMesh::VertexAttrib(unsigned int index, int size, int stride, const void* offset) {
        std::cout << "Mesh attrib config: " << index << std::endl;
        Bind();

        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(index);

        Unbind();
    }

    void SimpleMesh::Bind() {
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        // std::cout << "Bind [VAO: " << m_VAO << ", VBO: " << m_VBO << ", EBO: " << m_EBO << "]" << std::endl;
    }

    void SimpleMesh::Unbind() {
        // std::cout << "Mesh unbind\n";
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}