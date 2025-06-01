namespace Simpleton {
    class SimpleMesh {
        private:
            unsigned int m_VAO, m_VBO, m_EBO;
            unsigned int m_vertSize, m_indSize;

        public:
            SimpleMesh(float* vertices, int vertSize, int* indices, int indSize);
            void Terminate();

            void Bind();
            void Unbind();

            void VertexAttrib(unsigned int index, int size, int stride, const void* offset);
            void Draw();
    };
}