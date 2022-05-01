#pragma once
#include <SFML/Graphics.hpp>
#include "Baza.hpp"
#include <cmath>
class Fire : public Baza
{
public:
    Fire(
        Animation& anim, float x, float y, float angle = 0.0f,
        float radius = 1.0f) : Baza("bullet", anim, x, y, angle, radius) {}

private:
    void update_impl() override
    {
        m_dx = std::cos(m_angle * m_anim.k_deg_to_rad) * 6;
        m_dy = std::sin(m_angle * m_anim.k_deg_to_rad) * 6;
        move();

        if (is_out_of_bounds())
        {
            die();
        }
    }
};
