#pragma once


#include "../../../../../../../interaction/event/button/simple/buttonEventSimple.h"

namespace ui {
    class LayerWithMovableBorder;
    class MovableBorderEvent : public ButtonEvent_Simple {
    protected:
        LayerWithMovableBorder* layer;
        sf::Vector2i startMousePosition;
        float startBorderValue;
        bool active;

        void copy(MovableBorderEvent* event);

        void startPressed(sf::Vector2i mousePosition) override;

        void stopPressed (sf::Vector2i mousePosition) override;

        void whilePressed(sf::Vector2i mousePosition) override;

        void whileNotPressed  (sf::Vector2i mousePosition) override;

    public:
        explicit MovableBorderEvent(LayerWithMovableBorder &layer);

        void setLayer(LayerWithMovableBorder& layer);

        MovableBorderEvent* copy() override;

    };
}



