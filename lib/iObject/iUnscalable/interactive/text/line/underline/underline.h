#pragma once

#include "../baseLine.h"

namespace ui {
    class Underline : public BaseLine{
    protected:
        float underlineOffset;
        float underlineThickness;
    public:
        Underline(sf::Color color = sf::Color{255, 255, 255, 0});
        void init(uint size, sf::Font &font, sf::Color color, sf::RenderTarget &renderTarget);
        void resize(float start, float end, float height);
    protected:
        void init(float underlineOffset, float underlineThickness, sf::VertexArray vertexArray, sf::RenderTarget &renderTarget);
    public:
        Underline* copy();
    };
}