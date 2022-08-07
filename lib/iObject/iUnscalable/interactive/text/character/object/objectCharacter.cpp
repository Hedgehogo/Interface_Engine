#include "objectCharacter.h"
#include "iostream"

namespace ui {
    ObjectCharacter::ObjectCharacter(ui::IObject* object) : object(object){}

    wchar_t ObjectCharacter::getChar() {
        return '\0';
    }

    void ObjectCharacter::setPosition( sf::Vector2f position) {
        position.y -= getHeight();
        BaseCharacter::setPosition(position);
        object->setPosition(position);
    }

    void ObjectCharacter::move(sf::Vector2f position) {
        BaseCharacter::move(position);
        object->move(position);
    }

    float ObjectCharacter::getHeight() {
        return object->getAreaSize().y;
    }

    float ObjectCharacter::getAdvance() {
        return object->getAreaSize().x;
    }

    float ObjectCharacter::getKerning(wchar_t character) {
        return 0;
    }

    BaseCharacter::Special ObjectCharacter::isSpecial() {
        return BaseCharacter::Special::no;
    }

    void ObjectCharacter::draw() {}

    ObjectCharacter::~ObjectCharacter() {
        delete object;
    }

    void ObjectCharacter::drawDebug(sf::RenderTarget &renderTarget, int indentAddition, uint hue, uint hueOffset) {
        object->drawDebug(renderTarget, 0, indentAddition, hue, hueOffset);
    }

    std::vector<BaseLine *> & ObjectCharacter::getLine() {
        return lines;
    }
}