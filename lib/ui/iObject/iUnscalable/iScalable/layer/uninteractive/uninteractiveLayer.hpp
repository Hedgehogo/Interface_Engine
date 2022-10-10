#pragma once

#include "../../uninteractive/uninteractive.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"
#include "../layer.hpp"

namespace ui {
    class UninteractiveLayer : public IUninteractive, public LayoutWithObject, public Layer{
    public:
        UninteractiveLayer(IScalable* object, sf::Vector2f minSize = {0, 0});

        void resize(sf::Vector2f size, sf::Vector2f position) override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        UninteractiveLayer* copy() override;
    };
	
	bool convertPointer(const YAML::Node &node, UninteractiveLayer *&uninteractiveLayer);
}