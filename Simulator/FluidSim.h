//
// Created by apgra on 11/27/2023.
//

#ifndef APPLICATION_FLUIDSIM_H
#define APPLICATION_FLUIDSIM_H


#include <vector>
#include "../Engine/Bounds2D.h"

struct FluidSimConfig {
    Bounds2D bounds;

    int numParticles = 1;
};

struct FluidParticle {
    FluidParticle(glm::vec2 pos) : position(pos) {

    }

    glm::vec2 position;
};

class FluidSim {
public:
    FluidSim(FluidSimConfig* config);

    void createParticles();

    void step(float dt);
    void draw();

    void reset();
private:

    void drawParticle(FluidParticle p);


private:
    FluidSimConfig* config;
    std::vector<FluidParticle> particles;
};


#endif //APPLICATION_FLUIDSIM_H
