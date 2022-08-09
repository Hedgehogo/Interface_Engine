
#include "strikeThrough.h"

namespace ui {
    ui::StrikeThrough::StrikeThrough(sf::Color color, float strikeThroughOffset) : BaseLine(sf::TriangleStrip, 4, color), strikeThroughOffset(strikeThroughOffset) {}

    void ui::StrikeThrough::init(uint size, sf::Font &font, sf::Color color, sf::RenderTarget &renderTarget) {
        BaseLine::init(size, font, color, renderTarget);

        strikeThroughOffset *= size;
        underlineThickness = font.getUnderlineThickness(size);
    }

    void ui::StrikeThrough::resize(float start, float end, float height) {
        vertexArray[0].position = {start, height - strikeThroughOffset - (underlineThickness/2)};
        vertexArray[1].position = {start, height - strikeThroughOffset + (underlineThickness/2)};
        vertexArray[2].position = {end  , height - strikeThroughOffset - (underlineThickness/2)};
        vertexArray[3].position = {end  , height - strikeThroughOffset + (underlineThickness/2)};
    }

    void StrikeThrough::init(float strikeThroughOffset, float underlineThickness, sf::VertexArray vertexArray, sf::RenderTarget &renderTarget) {
        this->strikeThroughOffset = strikeThroughOffset;
        this->underlineThickness = underlineThickness;
        this->renderTarget = &renderTarget;
        this->vertexArray = vertexArray;
    }

    StrikeThrough *ui::StrikeThrough::copy() {
        StrikeThrough* underline = new StrikeThrough(sf::Color(), 0);
        underline->init(strikeThroughOffset, underlineThickness, vertexArray, *renderTarget);
        return underline;
    }
}