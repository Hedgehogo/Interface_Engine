
#include "baseLine.hpp"

namespace ui {
    BaseLine::BaseLine(sf::PrimitiveType type, std::size_t vertexCount, sf::Color color) :vertexArray(type, vertexCount) {
        for (int i = 0; i < vertexArray.getVertexCount(); ++i)
            vertexArray[i].color = color;
    }

    void BaseLine::init(uint size, sf::Font &font, sf::Color color, sf::RenderTarget &renderTarget) {
        this->renderTarget = &renderTarget;

        if (vertexArray[0].color == sf::Color{255, 255, 255, 0})
            for (int i = 0; i < vertexArray.getVertexCount(); ++i)
                vertexArray[i].color = color;
    }

    void BaseLine::draw() {
        renderTarget->draw(vertexArray);
    }

    void BaseLine::move(sf::Vector2f position) {
        for (int i = 0; i < vertexArray.getVertexCount(); ++i)
            vertexArray[i].position += position;
    }
}
