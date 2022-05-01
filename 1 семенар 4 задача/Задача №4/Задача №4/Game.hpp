#pragma once
#include "Animation.hpp"
#include "Asteroids.hpp"
#include "Fire.hpp"
#include "Detonation.hpp"
#include "Players.hpp"

#include <iostream>
#include <memory>
#include <list>

class Game
{
public:
    Game() : app(sf::VideoMode(m_rock.W, m_rock.H), title)
    {
        init_app();
        init_texts();
        load_visuals();
    }

    void run()
    {
        init_game();
        game_loop();
    }

private:
    void init_game()
    {
        for (auto i = 0; i < initial_asteroids; ++i)
        {
            entities.push_back(std::make_shared<Asteroids>(
                m_rock, rand() % m_rock.W, rand() % m_rock.H, rand() % 360, 25));
        }

        p = std::make_shared<Players>(m_player, 200, 200, 0, 20);
        entities.push_back(p);

        text.setString("score: " + std::to_string(p->score()) + "\nLifes: "
            + std::to_string(p->lives()));
    }

    void init_app()
    {
        app.setFramerateLimit(60);
    }

    void init_texts()
    {
        text.setCharacterSize(character_size);
        text.setFillColor(sf::Color::Red);
    }

    void game_loop()
    {
        while (app.isOpen() && p->has_lives()) {
            poll_events();
            adjust_position();
            process_collisions();
            hit();
            update_explosions();
            spawn_new_asteroids();
            remove_dead_entities();
            redraw();
        }
    }

    void poll_events()
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                app.close();
            }

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Space)
            {
                fire();
            }
        }
    }

    void adjust_position()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            p->rotate_by_deg(3);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            p->rotate_by_deg(-3);
        }
        p->set_hit(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
    }

    void process_collisions()
    {
        for (const auto& a : entities)
        {
            for (const auto& b : entities)
            {
                if (a->name() == "asteroid" && b->name() == "bullet"
                    && Baza::collide(*a, *b))
                {
                    a->die();
                    b->die();

                    for (auto i = 0; i < 2; i++)
                    {
                        if (a->radius() == 15)
                        {
                            continue;
                        }
                        auto e = std::make_shared<Asteroids>(
                            m_small_rock, a->x(), a->y(), rand() % 360, 15);
                        entities.push_back(e);
                    }

                    p->inc_score();
                }

                if (a->name() == "player" && b->name() == "asteroid"
                    && Baza::collide(*a, *b))
                {
                    b->die();

                    p->respawn();
                }
            }
        }
    }

    void hit()
    {
        if (p->is_hit())
        {
            p->anim() = m_go_player;
        }
        else
        {
            p->anim() = m_player;
        }
    }

    void fire()
    {
        auto b = std::make_shared<Fire>(m_bullet, p->x(), p->y(), p->angle(), 10);
        entities.push_back(b);
    }

    void update_explosions()
    {
        for (const auto& e : entities)
        {
            if (e->name() == "explosion")
            {
                if (e->anim().is_end())
                {
                    e->die();
                }
            }
        }
    }

    void remove_dead_entities()
    {
        for (auto it = std::begin(entities); it != std::end(entities);)
        {
            auto& e = *it;

            e->update();

            if (!e->is_alive())
            {
                it = entities.erase(it);
            }
            else
            {
                std::advance(it, 1);
            }
        }
    }

    void spawn_new_asteroids()

    {
        if (!(rand() % 150))
        {
            auto a = std::make_shared<Asteroids>(
                m_rock, 0, rand() % m_rock.H, rand() % 360, 25);
            entities.push_back(a);
        }
    }

    void load_visuals()
    {
        t1.loadFromFile("images/spaceship.png");
        t2.loadFromFile("images/background.jpg");
        t3.loadFromFile("images/explosions.png");
        t4.loadFromFile("images/rock.jpg");
        t5.loadFromFile("images/fire.png");
        t6.loadFromFile("images/small_rock.png");

        t1.setSmooth(true);
        t2.setSmooth(true);

        m_sprite.setTexture(t2);

        m_explosion = Animation(t3, 0, 0, 256, 256, 48, 0.5);
        m_rock = Animation(t4, 0, 0, 64, 64, 16, 0.5);
        m_small_rock = Animation(t6, 0, 0, 64, 64, 16, 0.2);
        m_bullet = Animation(t5, 0, 0, 32, 64, 16, 1);
        m_player = Animation(t1, 40, 0, 40, 40, 2, 0);
        m_go_player = Animation(t1, 40, 40, 40, 40, 1, 0);
    }

    void redraw()
    {
        app.draw(m_sprite);
        for (const auto& i : entities)
        {
            i->draw(app);
        }
        app.display();
    }

private:
    const std::string title = "Asteroids!";
    const int initial_asteroids = 10;
    const int character_size = 25;

    sf::Text text;

    sf::RenderWindow app;

    sf::Texture t1, t2, t3, t4, t5, t6;

    sf::Sprite m_sprite;

    Animation m_explosion, m_rock, m_small_rock, m_bullet, m_player, m_go_player;

    std::shared_ptr<Players> p;

    std::list< std::shared_ptr<Baza> > entities;
};
