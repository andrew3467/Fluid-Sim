//
// Created by apgra on 11/27/2023.
//

#include "FluidSim.h"

#include "../Renderer/Renderer.h"

FluidSim::FluidSim(FluidSimConfig *c) : config(c) {
    createParticles();
}

void FluidSim::createParticles() {
    particles.clear();

    for(int i = 0; i < config->numParticles; i++){
        particles.emplace_back(
                glm::vec2(i, i)
                );
    }
}

void FluidSim::step(float dt) {

}

void FluidSim::reset() {
    createParticles();
}


void FluidSim::draw() {
    config->bounds.draw();

    //Draw particles
    for(auto& p : particles){
        drawParticle(p);
    }
}

void FluidSim::drawParticle(FluidParticle p) {
    glm::mat4 model = glm::scale(
            glm::translate(
                    glm::mat4(1.0f),
                    glm::vec3(p.position, 0.0f)
                    ),
                    glm::vec3(0.50f)
            );

    Shaders::solid_unlit->setMat4("model", model);

    Renderer::Renderer::DrawSquare(*Shaders::solid_unlit);
}