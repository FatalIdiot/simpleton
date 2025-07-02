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

    void Mesh::Terminate() {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
    }

    Mesh::Mesh() {
        InitMesh();
    }

    Mesh::Mesh(PrimitiveTypes type, const void* data, unsigned int size) {
        InitMesh();
        SetBufferData(type, data, size);
    }

    Mesh::~Mesh() {
        Terminate();
    }

    void Mesh::SetBufferData(PrimitiveTypes type, const void* data, unsigned int size) {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);  
        m_Type = type;
        if(size == m_DataSize) {
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        } else {
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        }
        
        m_DataSize = size;
    }

    void Mesh::SetAttributes(unsigned int* attributes, unsigned int count) {
        ClearAttributes();
        // Calculate stride
        for(unsigned int i = 0; i < count; i++) {
            m_AttribStride += attributes[i] * sizeof(float);
        }

        int offset = 0;
        for(unsigned int i = 0; i < count; i++) {
            glVertexAttribPointer(i, attributes[i], GL_FLOAT, GL_FALSE, m_AttribStride, (void*)offset);
            glEnableVertexAttribArray(i); 

            offset += attributes[i] * sizeof(float);
        }
    }

    void Mesh::AddAttribute(short componentCount) {
        glBindVertexArray(m_VAO);

        short attribIndex = GetAttribCount();

        unsigned int attributeSize = componentCount * sizeof(float);
        m_AttribStride += attributeSize;

        // Update sride in other attributes
        unsigned int offset = 0;
        for (int i = 0; i < m_Attributes.size(); i++) {
            glVertexAttribPointer(i, m_Attributes[i].componentCount, GL_FLOAT, GL_FALSE, m_AttribStride, (void*)offset);
            offset += m_Attributes[i].size;
        }

        glVertexAttribPointer(attribIndex, componentCount, GL_FLOAT, GL_FALSE, m_AttribStride, (void*)offset);
        glEnableVertexAttribArray(attribIndex); 

        m_Attributes.push_back({ componentCount, attributeSize });

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
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBindVertexArray(m_VAO);
    }

    void Mesh::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    int GetOpenGlType(PrimitiveTypes type) {
        switch(type) {
            case PrimitiveTypes::Points:
                return GL_POINTS;
            case PrimitiveTypes::Lines:
                return GL_LINES;
            case PrimitiveTypes::LineStrip:
                return GL_LINE_STRIP;
            case PrimitiveTypes::TriangleFan:
                return GL_TRIANGLE_FAN;
            default:
                return GL_TRIANGLES;
        }
    }

    void Mesh::Draw() {
        Bind();

        // Set global uniforms for current shader
        ShaderUniformManager::SetData();

        // Since in Interleaped data stride equals vertex data size, 
        // we can calculate number of elements based on entire buffer size and stride
        glDrawArrays(GetOpenGlType(m_Type), 0, m_DataSize / m_AttribStride);
        Unbind();
    }
}