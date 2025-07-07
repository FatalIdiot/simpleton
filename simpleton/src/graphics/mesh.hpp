#pragma once

#include <vector>

namespace Simpleton {
    struct MeshAttribute {
        unsigned int type; // OpenGL type of data
        unsigned int count;
        bool normalized = false;
    };

    class Mesh {
        private:
            unsigned int m_Type;
            unsigned int m_VBO;

            unsigned int m_VAO;
            std::vector<MeshAttribute> m_Attributes; // attributes data is saved for recalculations

            unsigned int m_EBO;

            unsigned int m_DataSize;
            unsigned int m_IndexCount;
            unsigned int m_AttribStride;

        public:
            Mesh();
            Mesh(unsigned int type, const void* data, unsigned int size);
            ~Mesh();

            // Vertex Buffer Object - must be Interleaved data
            void SetBufferData(unsigned int type, const void* data, unsigned int size);

            // Vertex Array Object
            void SetAttributes(MeshAttribute attributes[], short count); // Add all attributes as array
            void AddAttribute(MeshAttribute newAttribute); // Add attribute to the list
            void ClearAttributes();
            unsigned int GetAttribCount();
            void EnableAttribute(short index);
            void DisableAttribute(short index);

            // Element Buffer Object
            void SetIndexData(unsigned int* data, unsigned int count);
            void RemoveIndexData();

            void Bind();
            void Draw();

        private:
            void InitMesh();
            static unsigned int GetTypeSize(unsigned int type);
            void Terminate();
    };
}