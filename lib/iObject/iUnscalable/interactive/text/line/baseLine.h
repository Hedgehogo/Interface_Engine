#pragma once

#include <SFML/Graphics.hpp>

namespace ui {
    class BaseLine {
    protected:
        sf::RenderTarget* renderTarget;
        sf::VertexArray vertexArray;
    public:
        BaseLine(sf::PrimitiveType type, std::size_t vertexCount = 0, sf::Color color = sf::Color{255, 255, 255, 0});
        virtual void init(uint size, sf::Font &font, sf::Color color, sf::RenderTarget &renderTarget);

        virtual void draw();

        virtual void move(sf::Vector2f position);
        virtual void resize(float start, float end, float height) = 0;

        virtual BaseLine* copy() = 0;

        virtual ~BaseLine() = default;
    };
}