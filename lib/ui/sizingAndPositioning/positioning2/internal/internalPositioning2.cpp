#include "internalPositioning2.hpp"

namespace ui {
    InternalPositioning2::InternalPositioning2(sf::Vector2f coefficient) :
        horizontal(std::max(0.f, std::min(1.f, coefficient.x))), vertical(std::max(0.f, std::min(1.f, coefficient.y))){}

    void InternalPositioning2::init(sf::RenderTarget &renderTarget) {}

    sf::Vector2f InternalPositioning2::findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) {
        return {horizontal.findPosition(parentPosition.x, objectSize.x, parentSize.x, 0), vertical.findPosition(parentPosition.y, objectSize.y, parentSize.y, 0)};
    }

    InternalPositioning2::InternalPositioning2(InternalPositioning vertical, InternalPositioning horizontal) : vertical(vertical), horizontal(horizontal) {}

    InternalPositioning2 *InternalPositioning2::copy() {
        return new InternalPositioning2{*horizontal.copy(), *vertical.copy()};
    }
}