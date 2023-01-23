#pragma once
#include "../layer.hpp"
#include "../../interactive/simple/interactiveSimple.hpp"
#include "../../../../layout/twoObjects/layoutWithTwoObjects.hpp"
#include "../../../../../interaction/iInteraction/block/pressed/pressedInteraction.hpp"
#include "interaction/event/movableBorderEvent.hpp"
#include "../../../../../animation/variables/base/animationVariable.hpp"
#include "../../../../../animation/convertToUse/coefficientWithRange/convertToUseCoefficientWithRange.hpp"

namespace ui{
    class LayerWithMovableBorder : public Layer, public LayoutWithTwoObjects, public Interactive_Simple {
        PressedInteraction pressedInteraction;
        float borderValueNow;
	    AnimationVariable<float>& borderValue;
        int borderInteractionSize;
		bool isHorizontalBorder;
		
    public:
		void init(InitInfo initInfo) override;
		
		void init(InteractiveInitInfo interactiveInitInfo) override;
	
		LayerWithMovableBorder(IScalable *firstObject, IScalable *secondObject, bool isHorizontalBorder ,
		                       AnimationVariable<float>& borderValue = *(new AnimationVariable<float>{0.5, new ConvertToUseCoefficientWithRange<float>{}}),
		                       int borderInteractionSize = 5, sf::Vector2f minSize = {0, 0});

        float getBorderValue();

        void setBorderValue(float borderValue);

        float getBorderValueNow();

        int getBorderInteractionSize();

        void setBorderInteractionSize(int size);

        bool getIsHorizontalBorder();

        bool isInBorder(sf::Vector2f pointPosition);
	
		void update() override;
	
		bool updateInteractions(sf::Vector2f mousePosition) override;

        void resize(sf::Vector2f size, sf::Vector2f position) override;

        sf::Vector2f getMinSize() override;

        sf::Vector2f getNormalSize() override;

        LayerWithMovableBorder* copy() override;
	
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, LayerWithMovableBorder *&layerWithMovableBorder);
	
	typedef LayerWithMovableBorder LayerWMovableB;
	typedef LayerWithMovableBorder LWMB;
}