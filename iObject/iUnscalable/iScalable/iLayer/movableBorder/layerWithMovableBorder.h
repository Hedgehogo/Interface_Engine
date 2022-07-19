#pragma once
#include "../iLayer.h"
#include "../../interactiveSimple/interactiveSimple.h"
#include "interaction/event/movableBorderEvent.h"
#include "../../../../../interaction/iInteraction/block/pressed/pressedInteraction.h"

namespace ui{
    class LayerWithMovableBorder : public ILayer, public Interactive_Simple {
        IScalable *firstObject;
        IScalable *secondObject;

        PressedInteraction pressedInteraction;

        bool isHorizontalBorder;
        float borderValue;
        float borderValueNow;
        int borderInteractionSize;

        void init(sf::RenderTarget &renderTarget, PanelManager &panelManager) override;

    public:
        LayerWithMovableBorder(IScalable *firstObject, IScalable *secondObject, bool isHorizontalBorder , float borderValue = 0.5, int borderInteractionSize = 5, sf::Vector2f minSize = {0, 0});

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
	
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
    };
	
	typedef LayerWithMovableBorder LayerWMovableB;
	typedef LayerWithMovableBorder LWMB;
}