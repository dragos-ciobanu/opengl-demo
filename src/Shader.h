//
// Created by dragos on 30.04.21.
//

#ifndef HAND_SHADER_H
#define HAND_SHADER_H

#include <string>
#include <unordered_map>

struct ShaderSources
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    unsigned int m_RendererId;
    std::string m_filePath;
    std::unordered_map<std::string, int> m_UniformLocationCache;
    int getUniformLocation(const std::string& name);
    static unsigned int createShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
    static unsigned int compileShader(unsigned int type, const std::string& source);
    static ShaderSources parseShader(const std::string& filepath);
public:
    Shader(const std::string&  filePath);
    ~Shader();
    void Bind() const;
    void Unbind() const;
    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
};
#endif //HAND_SHADER_H