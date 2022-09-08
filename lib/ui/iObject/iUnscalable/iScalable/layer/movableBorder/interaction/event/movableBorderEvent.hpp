#pragma once


#include "../../../../../../../interaction/event/button/simple/buttonEventSimple.hpp"

namespace ui {
    class LayerWithMovableBorder;
    class MovableBorderEvent : public ButtonEvent_Simple {
    protected:
        LayerWithMovableBorder* layer;
        sf::Vector2i startMousePosition;
        float startBorderValue;
        bool active;

        void copy(MovableBorderEvent* event);

        void startPressed() override;

        void stopPressed() override;

        void whilePressed() override;

        void whileNotPressed() override;

    public:
        explicit MovableBorderEvent(LayerWithMovableBorder &layer);

        void setLayer(LayerWithMovableBorder& layer);

        MovableBorderEvent* copy() override;

    };
}



