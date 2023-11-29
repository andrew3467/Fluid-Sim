//
// Created by apgra on 11/27/2023.
//

#include <glad/glad.h>
#include "Bounds2D.h"

#include "../Renderer/Renderer.h"


Bounds2D::Bounds2D() {
    center = glm::vec2(0.0f);
    offset = glm::vec2(1.0f);
}

Bounds2D::Bounds2D(glm::vec2 center, glm::vec2 offset) : center(center), offset(offset) {

}

Bounds2D::~Bounds2D() {

}

void Bounds2D::draw() {
    glm::mat4 model = glm::scale(
            glm::translate(
                    glm::mat4(1.0f),
                    glm::vec3(center, 0.0f)
                    ),
                    glm::vec3(offset, 1.0f));

    Shaders::solid_unlit->setMat4("model", model);

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    Renderer::Renderer::DrawSquare(*Shaders::solid_unlit, GL_LINE_LOOP);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
}
