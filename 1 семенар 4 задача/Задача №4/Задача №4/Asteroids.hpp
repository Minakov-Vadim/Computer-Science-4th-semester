#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "Animation.hpp"
#include <ctime>
#include "Baza.hpp"
class Asteroids : public Baza
{
public:
    Asteroids(
        Animation& anim, float x, float y, float angle = 0.0f,
        float radius = 1.0f) : Baza("asteroid", anim, x, y, angle, radius)
    {
        std::random_device dev;
        std::default_random_engine engine(dev());
        m_dx = static_cast<float>(std::uniform_int_distribution<int>(-4, 4)(engine));
        m_dy = static_cast<float>(std::uniform_int_distribution<int>(-4, 4)(engine));
    }

private:
    void update_impl() override
    {
        move();
        wrap();
    }
};
