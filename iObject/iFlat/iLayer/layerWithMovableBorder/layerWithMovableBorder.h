#pragma once
#include "../iLayer.h"
#include "../../iInteractive/simple/interactiveSimple.h"
#include "interaction/event/movableBorderEvent.h"
#include "../../../../interaction/iInteraction/block/pressed/pressedInteraction.h"

namespace ui{
    class LayerWithMovableBorder : public ILayer, public Interactive_Simple {
        IFlat *firstObject;
        IFlat *secondObject;

        PressedInteraction pressedInteraction;

        bool isHorizontalBorder;
        float borderValue;
        float borderValueNow;
        int borderInteractionSize;

        void init(sf::RenderWindow &window, PanelManager &panelManager) override;

    public:
        LayerWithMovableBorder(IFlat *firstObject, IFlat *secondObject, bool isHorizontalBorder , float borderValue = 0.5,int borderInteractionSize = 5, sf::Vector2f minSize = {0, 0});

        ~LayerWithMovableBorder() override;

        float getBorderValue();

        void setBorderValue(float borderValue);

        float getBorderValueNow();

        int getBorderInteractionSize();

        void setBorderInteractionSize(int size);

        bool getIsHorizontalBorder();

        bool isInBorder(sf::Vector2f pointPosition);

        void draw() override;

        void resize(sf::Vector2f size, sf::Vector2f position) override;

        bool updateInteractions(sf::Vector2f mousePosition) override;

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;

        void update() override;

        LayerWithMovableBorder* copy() override;
    };
}