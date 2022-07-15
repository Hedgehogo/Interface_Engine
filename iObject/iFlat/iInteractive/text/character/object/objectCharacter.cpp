#include "objectCharacter.h"

namespace ui {
    ObjectCharacter::ObjectCharacter(ui::IObject* object) : object(object){}

    wchar_t ObjectCharacter::getChar() {
        return '\0';
    }

    void ObjectCharacter::setPosition(const sf::Vector2f position) {
        BaseCharacter::setPosition(position);
        object->setPosition(position);
    }

    void ObjectCharacter::move(sf::Vector2f position) {
        position.y -= getHeight();
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

    void ObjectCharacter::draw() {
        object->draw();
    }

    ObjectCharacter::~ObjectCharacter() {
        delete object;
    }
}