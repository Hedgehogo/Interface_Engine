#pragma once

#include "../iLayer.h"
#include "../../iDrawable/iDrawable.h"

namespace ui {
	class LayerWithConstCenter : public ILayer {
	protected:
		IScalable *object;
		IDrawable *background;
		sf::Vector2f sizeOffset;
		float aspectRatio;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		void copy(LayerWithConstCenter* layerWithConstCenter);
	
	public:
		LayerWithConstCenter(IScalable *object, IDrawable *background, float aspectRatio, sf::Vector2f minSize = sf::Vector2f());
		
		~LayerWithConstCenter() override;
		
		void setAspectRatio(float aspectRatio);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		void update() override;
		
		LayerWithConstCenter* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithConstCenter LayerWCCenter;
	typedef LayerWithConstCenter LWCC;
}