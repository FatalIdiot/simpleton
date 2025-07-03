#pragma once

#include <vector>

namespace Simpleton {
    enum PrimitiveTypes {
        Points,
        Lines,
        LineStrip,
        Triangles,
        TriangleFan
    };

    typedef struct {
        unsigned int type; // OpenGL type of data
        unsigned int count;
        bool normalized;
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
            void SetAttributes(MeshAttribute attributes[], unsigned int count); // Add all attributes as array
            void AddAttribute(MeshAttribute newAttribute); // Add attribute to the list
            void ClearAttributes();
            unsigned int GetAttribCount();
            void EnableAttribute(short index);
            void DisableAttribute(short index);

            void Bind();
            void Unbind();
            void Draw();

        private:
            void InitMesh();
            static unsigned int GetTypeSize(unsigned int type);
            void Terminate();
    };
}