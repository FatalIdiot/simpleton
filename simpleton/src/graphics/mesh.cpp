#include "mesh.hpp"
#include "shaderUniformManager.hpp"

#include "glad/glad.h"

namespace Simpleton {
    void Mesh::InitMesh()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        m_AttribStride = 0;
    }

    unsigned int Mesh::GetTypeSize(unsigned int type) {
        switch(type) {
            case GL_BYTE:               return sizeof(bool);
            case GL_UNSIGNED_BYTE:      return sizeof(bool);
            case GL_SHORT:              return sizeof(short);
            case GL_UNSIGNED_SHORT:     return sizeof(unsigned short);
            case GL_INT:                return sizeof(int);
            case GL_UNSIGNED_INT:       return sizeof(unsigned int);
            case GL_FLOAT:              return sizeof(float);
            default:                    return 4;
        }
    }

    void Mesh::Terminate() {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);

        if(m_EBO != 0)
            glDeleteBuffers(1, &m_EBO);
    }

    Mesh::Mesh() {
        InitMesh();
    }

    Mesh::Mesh(unsigned int type, const void* data, unsigned int size) {
        InitMesh();
        SetBufferData(type, data, size);
    }

    Mesh::~Mesh() {
        Terminate();
    }

    void Mesh::SetBufferData(unsigned int type, const void* data, unsigned int size) {
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);  
        m_Type = type;
        if(size == m_DataSize) {
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        } else {
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        }
        
        m_DataSize = size;
    }

    void Mesh::SetAttributes(MeshAttribute attributes[], short count) {        
        ClearAttributes();
        
        // Calculate stride
        for(short i = 0; i < count; i++) {
            m_AttribStride += attributes[i].count * GetTypeSize(attributes[i].type);
        }

        int offset = 0;
        for(short i = 0; i < count; i++) {
            glVertexAttribPointer(i, attributes[i].count, attributes[i].type, attributes[i].normalized ? GL_TRUE : GL_FALSE, 
                m_AttribStride, (void*)offset);
            glEnableVertexAttribArray(i); 

            offset += attributes[i].count * GetTypeSize(attributes[i].type);

            m_Attributes.push_back({ attributes[i].type, attributes[i].count, attributes[i].normalized });
        }
    }

    void Mesh::AddAttribute(MeshAttribute newAttribute) {
        glBindVertexArray(m_VAO);

        short attribIndex = GetAttribCount();

        unsigned int attributeSize = newAttribute.count * GetTypeSize(newAttribute.type);
        m_AttribStride += attributeSize;

        // Update stride in other attributes
        unsigned int offset = 0;
        for (int i = 0; i < m_Attributes.size(); i++) {
            glVertexAttribPointer(i, m_Attributes[i].count, m_Attributes[i].type, m_Attributes[i].normalized ? GL_TRUE : GL_FALSE, 
                m_AttribStride, (void*)offset);
            offset += m_Attributes[i].count * GetTypeSize(m_Attributes[i].type);
        }

        glVertexAttribPointer(attribIndex, newAttribute.count, newAttribute.type, newAttribute.normalized ? GL_TRUE : GL_FALSE, 
            m_AttribStride, (void*)offset);
        glEnableVertexAttribArray(attribIndex); 

        m_Attributes.push_back(newAttribute);
    }

    void Mesh::ClearAttributes() {
        glBindVertexArray(m_VAO);

        m_AttribStride = 0;

        for (int i = 0; i < m_Attributes.size(); ++i) {
            glDisableVertexAttribArray(i);
        }
        m_Attributes.clear();
    }

    unsigned int Mesh::GetAttribCount() {
        return static_cast<short>(m_Attributes.size());
    }

    void Mesh::EnableAttribute(short index) {
        glEnableVertexAttribArray(index); 
    }

    void Mesh::DisableAttribute(short index) {
        glDisableVertexAttribArray(index);
    }

    void Mesh::Bind() {
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        if(m_EBO != 0)
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    }

    void Mesh::SetIndexData(unsigned int* data, unsigned int count) {
        glBindVertexArray(m_VAO);
        if(m_EBO == 0)
            glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_STATIC_DRAW); 
        m_IndexCount = count;
    }

    void Mesh::RemoveIndexData() {
        if(m_EBO == 0)
            return;
        int currentEBO;
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentEBO);
        if(m_EBO == static_cast<unsigned int>(currentEBO))
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDeleteBuffers(1, &m_EBO);
        m_EBO = 0;
        m_IndexCount = 0;
    }

    void Mesh::Draw() {
        Bind();

        // Set global uniforms for current shader
        ShaderUniformManager::SetData();

        if(m_EBO != 0) { // If EBO is set we draw with EBO
            glDrawElements(m_Type, m_IndexCount, GL_UNSIGNED_INT, 0);
        } else {
            // Since in Interleaped data stride equals vertex data size, 
            // we can calculate number of elements based on entire buffer size and stride
            glDrawArrays(m_Type, 0, m_DataSize / m_AttribStride);
        }
    }
}