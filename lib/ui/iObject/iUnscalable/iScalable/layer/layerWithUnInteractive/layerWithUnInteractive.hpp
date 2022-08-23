#pragma once

#include "../../uninteractive/unIteractive.hpp"
#include "../../../../layout/object/layoutWithObject.h"
#include "../layer.hpp"

namespace ui {
    class LayerWithUnInteractive : public IUninteractive, public LayoutWithObject, public Layer{
    public:
        LayerWithUnInteractive(IScalable* object, sf::Vector2f minSize = {0, 0});

        void resize(sf::Vector2f size, sf::Vector2f position) override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        LayerWithUnInteractive* copy() override;

        static LayerWithUnInteractive* createFromYaml(const YAML::Node &node);
    };
} // ui