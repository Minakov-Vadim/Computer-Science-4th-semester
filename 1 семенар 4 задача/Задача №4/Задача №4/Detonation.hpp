#pragma once
#include <SFML/Graphics.hpp>
#include "Baza.hpp"
#include <cmath>
class Explosion : public Baza
{
public:
    Explosion(
        Animation& anim, float x, float y, float angle = 0.0f,
        float radius = 1.0f) : Baza("explosion", anim, x, y, angle, radius) {}

private:
    void update_impl() override {}
};
