//
// Created by apgra on 9/11/2023.
//

#include "Renderer.h"

#include <glad/glad.h>

#define CIRLCE_RESOLUTION 32
void createCircleVertices(std::vector<glm::vec3> &v){
    int numVertices = CIRLCE_RESOLUTION + 1;

    const float TWO_PI = 2 * 3.14159;
    float step = TWO_PI / (float)CIRLCE_RESOLUTION;

    for(int i = 0; i < numVertices; i++){
        float x = cos(i * step);
        float y = sin(i * step);

        v.emplace_back(x,y, 0.0f);
    }
}

namespace Renderer {
    void Renderer::Draw(unsigned int VAO, int count, const Shader& shader, unsigned int drawMode, bool drawIndexed) {
        glBindVertexArray(VAO);
        shader.bind();

        if(drawIndexed){
            glDrawElements(drawMode, count, GL_UNSIGNED_INT, nullptr);
        }else{
            glDrawArrays(drawMode, 0, count);
        }

        shader.unbind();
        glBindVertexArray(0);
    }

    void Renderer::DrawSquare(const Shader& shader, unsigned int drawMode) {
        static const float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };
        static const unsigned int indices[6] = {
                0, 1, 2,
                2, 3, 0
        };

        static unsigned int VAO = -1, VBO = -1, EBO = -1;

        if (VAO == -1) {
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);


            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (void *) 0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * sizeof(float), (void *) (sizeof(float) * 3));
        }

        Draw(VAO, 6, shader, drawMode);
    }

    void Renderer::DrawCube(const Shader &shader) {
        static unsigned int VAO = -1, VBO = -1, EBO = -1;

        if (VAO == -1) {
            static float vertices[] = {
                    -0.5, -0.5,  0.5, //0
                    0.5, -0.5,  0.5, //1
                    -0.5,  0.5,  0.5, //2
                    0.5,  0.5,  0.5, //3
                    -0.5, -0.5, -0.5, //4
                    0.5, -0.5, -0.5, //5
                    -0.5,  0.5, -0.5, //6
                    0.5,  0.5, -0.5  //7
            };

            static unsigned int indices[36] = {
                    //Top
                    2, 6, 7,
                    2, 3, 7,

                    //Bottom
                    0, 4, 5,
                    0, 1, 5,

                    //Left
                    0, 2, 6,
                    0, 4, 6,

                    //Right
                    1, 3, 7,
                    1, 5, 7,

                    //Front
                    0, 2, 3,
                    0, 1, 3,

                    //Back
                    4, 6, 7,
                    4, 5, 7
            };


            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);


            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void *) 0);
        }

        Draw(VAO, 36, shader);
    }

    void Renderer::DrawHollowCircle(const Shader &shader) {
        std::vector<glm::vec3> vertices;
        static unsigned int VAO = -1, VBO = -1;

        if(VAO == -1){
            createCircleVertices(vertices);

            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
        }

        Draw(VAO, vertices.size(), shader, GL_LINE_LOOP, false);
    }
}
