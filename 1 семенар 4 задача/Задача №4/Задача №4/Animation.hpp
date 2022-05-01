#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
public:
    Animation() = default;

    Animation(
        sf::Texture& t, int x, int y, int w, int h, int count, float speed) :
        m_speed(speed)
    {
        for (auto i = 0; i < count; ++i)
        {
            m_frames.emplace_back(x + i * w, y, w, h);
        }

        m_sprite.setTexture(t);
        m_sprite.setOrigin(static_cast<float>(w) / 2, static_cast<float>(h) / 2);
        m_sprite.setTextureRect(m_frames[0]);
    }

    void update()
    {
        m_frame += m_speed;

        auto n = static_cast<float>(m_frames.size());
        if (m_frame >= n)
        {
            m_frame -= n;
        }

        if (!m_frames.empty())
        {
            m_sprite.setTextureRect(m_frames[static_cast<std::size_t>(m_frame)]);
        }
    }

    bool is_end() const
    {
        return m_frame + m_speed >= static_cast<float>(m_frames.size());
    }

    sf::Sprite& sprite() { return m_sprite; }

public:
    static inline const auto W = sf::VideoMode::getDesktopMode().width;
    static inline const auto H = sf::VideoMode::getDesktopMode().height;

    static inline const auto k_deg_to_rad = 0.017453f;

private:
    float m_frame{ 0.0 };
    float m_speed{ 0.0 };
    std::vector< sf::Rect<int> > m_frames;
    sf::Sprite m_sprite;
};

