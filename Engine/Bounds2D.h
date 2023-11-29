//
// Created by apgra on 11/27/2023.
//

#ifndef APPLICATION_BOUNDS2D_H
#define APPLICATION_BOUNDS2D_H


#include <glm/vec2.hpp>

class Bounds2D {
public:
    Bounds2D();
    Bounds2D(glm::vec2 center, glm::vec2 offset);
    ~Bounds2D();

    glm::vec2 center;
    glm::vec2 offset;

public:
    void draw();
};


#endif //APPLICATION_BOUNDS2D_H
