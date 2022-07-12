#pragma once
#include "../../iFlat.h"
#include "../iLayer.h"
#include "../../iDrawn/iDrawn.h"

namespace ui {
	class LayerWithConstRatio : public ILayer {
	protected:
		IFlat *constObject;
		IFlat *secondObject;
		IDrawn *background;
		
		bool verticalSide;      //true = up
		bool horizontalSide;    //true = left
		sf::Vector2f constSize;
		sf::Vector2f secondSize;
		sf::Vector2f constPosition;
		sf::Vector2f secondPosition;
		bool renderSecond;
		const float aspectRatio;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		void copy(LayerWithConstRatio* layerWithConstRatio);
		
	public:
		LayerWithConstRatio(IFlat *constObject, IFlat *secondObject, IDrawn *background, float aspectRatio, Corner corner = Corner::UpLeft, sf::Vector2f minSize = {0, 0});

        ~LayerWithConstRatio() override;

		Corner getCorner();
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void update() override;
		
		LayerWithConstRatio* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithConstRatio LayerWCRatio;
	typedef LayerWithConstRatio LWCR;
}