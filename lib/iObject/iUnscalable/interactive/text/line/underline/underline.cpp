#include "underline.h"

#include <iostream>

namespace ui {
    Underline::Underline(sf::Color color) : BaseLine(sf::TriangleStrip, 4, color) {}

    void Underline::init(uint size, sf::Font &font, sf::Color color, sf::RenderTarget &renderTarget) {
        BaseLine::init(size, font, sf::Color(), renderTarget);

        underlineOffset = font.getUnderlinePosition(size);
        underlineThickness = font.getUnderlineThickness(size);
    }

    void Underline::resize(float start, float end, float height) {
        vertexArray[0].position = {start, height + underlineOffset - (underlineThickness/2)};
        vertexArray[1].position = {start, height + underlineOffset + (underlineThickness/2)};
        vertexArray[2].position = {end  , height + underlineOffset - (underlineThickness/2)};
        vertexArray[3].position = {end  , height + underlineOffset + (underlineThickness/2)};
    }

    void Underline::init(float underlineOffset, float underlineThickness, sf::VertexArray vertexArray, sf::RenderTarget &renderTarget) {
        this->underlineOffset = underlineOffset;
        this->underlineThickness = underlineThickness;
        this->renderTarget = &renderTarget;
        this->vertexArray = vertexArray;
    }

    Underline *Underline::copy() {
        Underline* underline = new Underline;
        underline->init(underlineOffset, underlineThickness, vertexArray, *renderTarget);
        return underline;
    }
}