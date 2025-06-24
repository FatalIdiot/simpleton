#pragma once

#include <vector>
#include "glad/glad.h"

namespace Simpleton {
    enum PrimitiveTypes {
        Points,
        Lines,
        LineStrip,
        Triangles,
        TriangleFan
    };

    typedef struct {
        short componentCount;
        unsigned int size;
    } MeshAttribute;

    class Mesh {
        private:
            PrimitiveTypes m_Type;
            unsigned int m_VBO;

            unsigned int m_VAO;
            std::vector<MeshAttribute> m_Attributes; // attributes data is saved for recalculations

            unsigned int m_DataSize;
            unsigned int m_AttribStride;
            PrimitiveTypes m_PrimitiveType;

        public:
            Mesh();
            Mesh(PrimitiveTypes type, const void* data, unsigned int size);
            ~Mesh();

            // Vertex Buffer Object - must be Interleaved data
            void SetBufferData(PrimitiveTypes type, const void* data, unsigned int size);

            // Vertex Array Object
            void SetAttributes(unsigned int* attributes, unsigned int count); // Add all attributes as array
            void AddAttribute(short componentCount); // Add attribute to the list
            void ClearAttributes();
            unsigned int GetAttribCount();
            void EnableAttribute(short index);
            void DisableAttribute(short index);

            void Bind();
            void Unbind();
            void Draw();

            void Terminate();

        private:
            void InitMesh();
    };
}