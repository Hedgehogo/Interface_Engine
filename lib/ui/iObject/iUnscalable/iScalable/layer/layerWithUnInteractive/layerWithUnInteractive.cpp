#include "layerWithUnInteractive.hpp"

namespace ui {
    LayerWithUnInteractive::LayerWithUnInteractive(IScalable *object, sf::Vector2f minSize) : LayoutWithObject(object), Layer(minSize) {}

    void LayerWithUnInteractive::resize(sf::Vector2f size, sf::Vector2f position) {
        LayoutWithObject::resize(size, position);
    }

    bool LayerWithUnInteractive::updateInteractions(sf::Vector2f mousePosition) {
        return IUninteractive::updateInteractions(mousePosition);
    }

    LayerWithUnInteractive *LayerWithUnInteractive::createFromYaml(const YAML::Node &node) {
        IScalable* object;
        sf::Vector2f minSize;
        node["object"] >> object;
        if (node["min-size"]) node["min-size"] >> minSize;
        return new LayerWithUnInteractive{object, minSize};
    }

    LayerWithUnInteractive *LayerWithUnInteractive::copy() {
        return new LayerWithUnInteractive{object->copy(), minimumSize};
    }
} // ui