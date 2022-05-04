#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "Animation.hpp"
#include "Baza.hpp"
#include <ctime>

const int size = 15;//using in Game.hpp

class Asteroids : public Baza
{
public:
    explicit Asteroids(
        Animation& anim, float x, float y, float angle = 0.0f,
        float radius = size * 1.0f) : Baza(Entity::Asteroid, anim, x, y, angle, radius),
        m_dx(m_distribution(m_engine)), m_dy(m_distribution(m_engine))
    {}

private:
    static inline std::random_device m_dev;
    static inline std::default_random_engine m_engine = std::default_random_engine(m_dev());
    static inline std::uniform_real_distribution<float>(-4, 4) m_distribution;

    void update_impl() override
    {
        move();
        wrap();
    }
};
