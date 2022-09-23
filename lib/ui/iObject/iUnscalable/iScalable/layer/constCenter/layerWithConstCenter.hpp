#pragma once

#include "../layer.hpp"
#include "../../uninteractive/uninteractive.hpp"
#include "../../uninteractive/onlyDrawable/empty/empty.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"
#include "../../../../layout/background/layoutWithBackground.hpp"
#include "../../../../layout/twoObjects/layoutWithTwoObjects.hpp"
#include "../../uninteractive/onlyDrawable/empty/empty.hpp"

namespace ui {
	class LayerWithConstCenter : public Layer, public LayoutWithObject, public LayoutWithBackground, public LayoutWithTwoObjects, public IDrawable {
	protected:
		float aspectRatio;
		bool renderFirst;
		bool renderSecond;
		DrawManager firstDrawManager;
		DrawManager secondDrawManager;
	
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;

		LayerWithConstCenter(IScalable *object, IUninteractive *background, float aspectRatio, sf::Vector2f minSize = {});

		LayerWithConstCenter(IScalable *object, IScalable *firstObject, IScalable *secondObject, IUninteractive *background, float aspectRatio, sf::Vector2f minSize = {});

		void setAspectRatio(float aspectRatio);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithConstCenter* copy() override;
		
		static LayerWithConstCenter* createFromYaml(const YAML::Node &node);

		void draw() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithConstCenter LayerWCCenter;
	typedef LayerWithConstCenter LWCC;
}
