#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
//#include "vector.hpp"
#include "gravitationalObject.hpp"

using namespace sf;

void static render(RenderWindow& window, CircleShape& shape)
{
    window.draw(shape);
}

void static drawCircle(RenderWindow& window, float radius, Color color, sf::Vector2f position)
{
    CircleShape shape(radius, 100.0f);
    shape.setFillColor(color);
    shape.setPosition(position);
    window.draw(shape);
}

int main()
{
    double delta_time = 50.0;

    Vector2f camera_pos{ 0.0f, 0.0f };

    unsigned int width = 400;
    unsigned int height = 400;

    double scale = 150000.0;

    RenderWindow window(VideoMode(width, height), L"Новый проект", Style::Default);

    window.setFramerateLimit(60);

    window.setVerticalSyncEnabled(true);

    std::vector<float> position = { 100.0f, 100.0f };

    CircleShape shape(100.0f, 5.0f);
    shape.setFillColor(Color::Magenta);

    std::vector<GravitationalObject> objects{
        GravitationalObject({2000000.0 + 6378137.0, 0.0, 0.0}, {0.0, 7844.0, 0.0}, 1000, 1737000, {255, 255, 255}),
        GravitationalObject({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 5.9742e24, 6378137, {0, 255, 0})
    };


    while (window.isOpen())
    {
        shape.setPosition(position[0], position[1]);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::Resized)
            {
                sf::FloatRect Area(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(Area));
            }
        }

        //std::cout << objects[0].GetVelocity().x << " " << objects[0].GetVelocity().y <<"\n";

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            camera_pos.x += 3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            camera_pos.x -= 3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            camera_pos.y += 3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            camera_pos.y -= 3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            scale /= 1.05;
            camera_pos.x *= 1.05;
            camera_pos.y *= 1.05;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            scale *= 1.05;
            camera_pos.x /= 1.05;
            camera_pos.y /= 1.05;
        }

        for (int i = 0; i < objects.size(); i++)
        {
            for (int j = 0; j < objects.size(); j++)
            {
                if (j != i)
                {
                    objects[i].CalcGravForce(objects[j], delta_time);
                }
            }
            objects[i].MoveOnestep(delta_time);
            objects[i].Render(window, scale, camera_pos);
        }

        //render(window, shape);
        window.display();
        window.clear(Color::Black);
    }
    return 0;
}
