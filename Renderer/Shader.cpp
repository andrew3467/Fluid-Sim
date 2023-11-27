//
// Created by apgra on 9/12/2023.
//

#define VERTEX_INDEX 0
#define FRAGMENT_INDEX 1

#include "Shader.h"


#include <glad/glad.h>
#include "Shader.h"

    Shader::Shader() : m_Handle(0) {

    }

    Shader::Shader(const char *path) {
        m_Handle = createShaderProgram(path);
    }

    unsigned int Shader::createShaderProgram(const char *path) {
        unsigned int id = glCreateProgram();
        unsigned int vert, frag;
        auto shaders = parseShader(path); //Vertex: 0 Fragment: 1

        vert = createShader(GL_VERTEX_SHADER, shaders[0].c_str());
        frag = createShader(GL_FRAGMENT_SHADER, shaders[1].c_str());

        glAttachShader(id, vert);
        glAttachShader(id, frag);
        glLinkProgram(id);

        int success;
        char infoLog[512];
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::LINKING_FAILURE\n" << infoLog << "\n";
        }

        //Cleanup
        glDeleteShader(vert);
        glDeleteShader(frag);

        return id;
    }

    std::vector<std::string> Shader::parseShader(const char *path) {
        std::vector<std::string> shaders(2);
        std::stringstream ss;
        std::ifstream file(path);


        std::string line;
        std::string src;
        int curShader = 0;

        while (std::getline(file, line)) {
            if (line == "#vertex") {
                curShader = VERTEX_INDEX;
                src.clear();
            } else if (line == "#fragment") {
                shaders[curShader] = src;
                curShader = FRAGMENT_INDEX;
                src.clear();
            } else {
                src.append(line + "\n" );
            }
        }

        //Assumes fragment is final lit_shader
        shaders[curShader] = src;

        return shaders;
    }


    unsigned int Shader::createShader(unsigned int SHADER_TYPE, const char *src) {
        unsigned int shader = glCreateShader(SHADER_TYPE);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            auto e = std::string("ERROR::").
                    append((SHADER_TYPE == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT").
                    append("::SHADER::COMPILATION_FAILED\n").
                    append(infoLog).
                    append("\n");
            throw std::runtime_error(e);
        }

        return shader;
    }

    void Shader::bind() const {
        glUseProgram(m_Handle);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    int Shader::getUniformLocation(const std::string &name) const {
        if (m_UniformCache.find(name) != m_UniformCache.end()) {
            return m_UniformCache[name];
        }

        int location = glGetUniformLocation(m_Handle, name.c_str());
        m_UniformCache[name] = location;

        return location;
    }


    void Shader::setInt(const std::string &name, int v) {
        glUniform1i(getUniformLocation(name), v);
    }

    void Shader::setFloat(const std::string &name, float v) {
        glUniform1f(getUniformLocation(name), v);
    }


    void Shader::setVec2(const std::string &name, glm::vec2 v) {
        glUniform2f(getUniformLocation(name), v.x, v.y);
    }

    void Shader::setVec2(const std::string &name, float x, float y) {
        glUniform2f(getUniformLocation(name), x, y);
    }


    void Shader::setVec3(const std::string &name, glm::vec3 v) {
        glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
    }

    void Shader::setVec3(const std::string &name, float x, float y, float z) {
        glUniform3f(getUniformLocation(name), x, y, z);
    }

    void Shader::setVec3(const std::string &name, float v) {
        glUniform3f(getUniformLocation(name), v, v, v);
    }

    void Shader::setVec4(const std::string &name, glm::vec4 v) {
        glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
    }

    void Shader::setVec4(const std::string &name, float x, float y, float z, float w) {
        glUniform4f(getUniformLocation(name), x, y, z, w);
    }


    void Shader::setMat4(const std::string &name, glm::mat4 v) {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(v));
    }


//Cleanup
    Shader::~Shader() {
        glDeleteProgram(m_Handle);
    }

    void Shader::setPointLight(std::string& arrIndex, PointLight &light) {
        setVec3("pointLights[" + arrIndex + "].Position", light.Position);

        setVec3("pointLights[" + arrIndex + "].Ambient", light.Ambient);
        setVec3("pointLights[" + arrIndex + "].Diffuse", light.Diffuse);
        setVec3("pointLights[" + arrIndex + "].Specular", light.Specular);

        setFloat("pointLights[" + arrIndex + "].Constant", light.Constant);
        setFloat("pointLights[" + arrIndex + "].Linear", light.Linear);
        setFloat("pointLights[" + arrIndex + "].Exp", light.Exp);
    }

void Shader::initializeShaders() {
    Shaders::solid_unlit = new Shader("../Engine/Shaders/solid_unlit.glsl");
    Shaders::solid_lit = new Shader("../Engine/Shaders/solid_lit.glsl");
}
