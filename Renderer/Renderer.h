//
// Created by apgra on 9/11/2023.
//

#ifndef APPLICATION_RENDERER_H
#define APPLICATION_RENDERER_H

//Copied from glad.h, avoid including header
#define GL_TRIANGLES 0x0004

#include "Shader.h"

namespace Renderer {
    class Renderer {
    public:
        static void DrawSquare(const Shader& shader, unsigned int drawMode = GL_TRIANGLES);
        static void DrawHollowCircle(const Shader &shader);
        static void DrawCube(const Shader& shader);
        static void Draw(unsigned int VAO, int count, const Shader& shader, unsigned int drawMode = GL_TRIANGLES, bool drawIndexed = true);
    };
}


#endif //APPLICATION_RENDERER_H
