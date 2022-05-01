#pragma once
#include <SFML/Graphics.hpp>
#include "Baza.hpp"
#include <cmath>
class Players : public Baza
{
public:
    Players(
        Animation& anim, float x, float y, float angle = 0.0f,
        float radius = 1.0f) : Baza("player", anim, x, y, angle, radius) {}

    void respawn()
    {
        m_x = m_anim.W / 2;
        m_y = m_anim.H / 2;
        m_angle = 0;
        m_radius = 20;
        --m_lives;
    }

    bool has_lives() const
    {
        return m_lives > 0;
    }
    void inc_score()
    {
        ++m_score;
    }
    void set_hit(bool enable)
    {
        m_hit = enable;
    }
    bool is_hit() const
    {
        return m_hit;
    }
    int lives() const { return m_lives; }
    int score() const { return m_score; }
private:
    const int initial_lives = 3;
    const float max_speed = 15.0f;
    const float motion_slowdown_coefficient = 0.99f;
    void update_impl() override
    {
        if (m_hit)
        {
            m_dx += std::cos(m_angle * m_anim.k_deg_to_rad) * 0.2;
            m_dy += std::sin(m_angle * m_anim.k_deg_to_rad) * 0.2;
        }
        else
        {
            m_dx *= motion_slowdown_coefficient;
            m_dy *= motion_slowdown_coefficient;
        }
        float speed = std::sqrt(m_dx * m_dx + m_dy * m_dy);
        if (speed > max_speed)
        {
            m_dx *= max_speed / speed;
            m_dy *= max_speed / speed;
        }

        move();
        wrap();
    }
    bool m_hit = false;
    int m_lives = initial_lives;
    int m_score = 0;
};
