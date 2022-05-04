#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Baza.hpp"

class Explosion : public Baza
{
public:
    explicit Explosion(
        Animation& anim, float x, float y, float angle = 0.0f,
        float radius = 1.0f) : Baza(Entity::Explosion, anim, x, y, angle, radius) {}

private:
    void update_impl() override {}
};
