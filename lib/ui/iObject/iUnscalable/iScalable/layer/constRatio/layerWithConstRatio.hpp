#pragma once
#include "../layer.hpp"
#include "../../iScalable.hpp"
#include "../../uninteractive/uninteractive.hpp"
#include "../../uninteractive/onlyDrawable/empty/empty.hpp"
#include "../../../../layout/background/layoutWithBackground.hpp"
#include "../../../../layout/twoObjects/layoutWithTwoObjects.hpp"

namespace ui {
	class LayerWithConstRatio : public Layer, public LayoutWithBackground, public LayoutWithTwoObjects, public IDrawable {
	protected:
		DrawManager secondDrawManager;
		bool verticalSide, horizontalSide;      //true = up   true = left
		bool renderSecond;
		float aspectRatio;
		
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;
		
		void copy(LayerWithConstRatio* layerWithConstRatio);
		
	public:
		LayerWithConstRatio(IScalable *constObject, IScalable *secondObject, IUninteractive *background, float aspectRatio, Corner corner = Corner::upLeft, sf::Vector2f minSize = {0, 0});

		Corner getCorner();
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithConstRatio* copy() override;
		
		static LayerWithConstRatio* createFromYaml(const YAML::Node &node);
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithConstRatio LayerWCRatio;
	typedef LayerWithConstRatio LWCR;
}