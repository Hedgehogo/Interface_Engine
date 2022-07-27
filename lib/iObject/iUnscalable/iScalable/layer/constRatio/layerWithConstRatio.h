#pragma once
#include "../layer.h"
#include "../../iScalable.h"
#include "../../onlyDrawable/onlyDrawable.h"
#include "../../../../layout/background/layoutWithBackground.h"
#include "../../../../layout/twoObjects/layoutWithTwoObjects.h"

namespace ui {
	class LayerWithConstRatio : public Layer, public LayoutWithBackground, public LayoutWithTwoObjects, public IDrawable {
	protected:
		DrawManager secondDrawManager;
		bool verticalSide, horizontalSide;      //true = up   true = left
		bool renderSecond;
		float aspectRatio;
		
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		void copy(LayerWithConstRatio* layerWithConstRatio);
		
	public:
		LayerWithConstRatio(IScalable *constObject, IScalable *secondObject, OnlyDrawable *background, float aspectRatio, Corner corner = Corner::UpLeft, sf::Vector2f minSize = {0, 0});

		Corner getCorner();
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithConstRatio* copy() override;
		
		void draw() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithConstRatio LayerWCRatio;
	typedef LayerWithConstRatio LWCR;
}