#include "uninteractiveLayer.hpp"

namespace ui {
    UninteractiveLayer::UninteractiveLayer(IScalable *object, sf::Vector2f minSize) : LayoutWithObject(object), Layer(minSize) {}

    void UninteractiveLayer::resize(sf::Vector2f size, sf::Vector2f position) {
        LayoutWithObject::resize(size, position);
    }

    bool UninteractiveLayer::updateInteractions(sf::Vector2f mousePosition) {
        return IUninteractive::updateInteractions(mousePosition);
    }

    UninteractiveLayer *UninteractiveLayer::createFromYaml(const YAML::Node &node) {
        IScalable* object;
        sf::Vector2f minSize;
        node["object"] >> object;
        if (node["min-size"]) node["min-size"] >> minSize;
        return new UninteractiveLayer{object, minSize};
    }

    UninteractiveLayer *UninteractiveLayer::copy() {
        return new UninteractiveLayer{object->copy(), minimumSize};
    }
} // ui