namespace Simpleton {
    class SimpleShader {
        private:
            unsigned int m_ShaderProgId;

        public:
            SimpleShader();
            SimpleShader(const char* vartexShader, const char* fragmentShader);

            void SetUniform1i(const char* name, int i);
            void SetUniform4f(const char* name, float x, float y, float z, float w);
            void SetUniformMatrix4fv(const char* name, const float* value, const bool transpose);

            bool CompileShader(const char* vartexShader, const char* fragmentShader);
            void Use();
    };
}