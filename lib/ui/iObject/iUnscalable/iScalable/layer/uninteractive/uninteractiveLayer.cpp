#include "uninteractiveLayer.hpp"

namespace ui {
    UninteractiveLayer::UninteractiveLayer(IScalable *object, sf::Vector2f minSize) : LayoutWithObject(object), Layer(minSize) {}

    void UninteractiveLayer::resize(sf::Vector2f size, sf::Vector2f position) {
        LayoutWithObject::resize(size, position);
    }

    bool UninteractiveLayer::updateInteractions(sf::Vector2f mousePosition) {
        return IUninteractive::updateInteractions(mousePosition);
    }

    bool convertPointer(const YAML::Node &node, UninteractiveLayer *&uninteractiveLayer) {
        IScalable* object;
        sf::Vector2f minSize;
        node["object"] >> object;
        if (node["min-size"]) node["min-size"] >> minSize;
        { uninteractiveLayer = new UninteractiveLayer{object, minSize}; return true; }
    }

    UninteractiveLayer *UninteractiveLayer::copy() {
        return new UninteractiveLayer{object->copy(), minimumSize};
    }
} // ui