#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Animation.hpp"
class Baza
{
public:
    static bool collide(const Baza& a, const Baza& b)
    {
        return (b.m_x - a.m_x) * (b.m_x - a.m_x) + (b.m_y - a.m_y) * (b.m_y - a.m_y) <
            (a.m_radius + b.m_radius) * (a.m_radius + b.m_radius);
    }

    Baza(
        std::string name,
        Animation& anim, float x, float y, float angle = 0.0f,
        float radius = 1.0f) :
        m_anim(anim), m_x(x), m_y(y), m_angle(angle), m_radius(radius),
        m_name(std::move(name)) {}

    virtual bool is_alive() const
    {
        return m_is_alive;
    }

    void die()
    {
        m_is_alive = false;
    }

    void rotate_by_deg(float angle)
    {
        m_angle += angle;
    }

    void update()
    {
        update_impl();
        m_anim.update();
    }

    void draw(sf::RenderWindow& app)
    {
        m_anim.sprite().setPosition(m_x, m_y);
        m_anim.sprite().setRotation(m_angle + 90);
        app.draw(m_anim.sprite());
    }

    virtual ~Baza() = default;

public:
    float x() const { return m_x; }
    float y() const { return m_y; }
    float angle() const { return m_angle; }
    float radius() const { return m_radius; }
    const std::string& name() const { return m_name; }

    const Animation& anim() const { return m_anim; }
    Animation& anim() { return m_anim; }

protected:
    void move()
    {
        m_x += m_dx;
        m_y += m_dy;
    }

    void wrap()
    {
        if (m_x > static_cast<float>(m_anim.W)) { m_x = 0; }
        if (m_x < 0) { m_x = static_cast<float>(m_anim.W); }
        if (m_y > static_cast<float>(m_anim.H)) { m_y = 0; }
        if (m_y < 0) { m_y = static_cast<float>(m_anim.H); }
    }

    bool is_out_of_bounds() const
    {
        return m_x > m_anim.W || m_x < 0 || m_y > m_anim.H || m_y < 0;
    }

protected:
    Animation m_anim;

    float m_x;
    float m_y;
    float m_radius;
    float m_angle;

    bool m_is_alive = true;
    std::string m_name;

    float m_dx = 0.0;
    float m_dy = 0.0;
private:
    virtual void update_impl() = 0;
};
