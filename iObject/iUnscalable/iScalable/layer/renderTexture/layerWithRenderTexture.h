#pragma once
#include "../layer.h"
#include "../../../../layout/object/layoutWithObject.h"

namespace ui {
	class LayerWithRenderTexture : public Layer, public LayoutWithObject {
	protected:
		InteractionManager* interactionManager;
		sf::RenderTarget* renderTarget;
		sf::RenderTexture renderTexture;
		sf::Sprite sprite;
		bool optimize;
		bool active;
		
		void copy(LayerWithRenderTexture* layerWithRenderTexture);
		
	public:
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		LayerWithRenderTexture(IScalable* object, bool optimize = true, sf::Vector2f minSize = {});
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		LayerWithRenderTexture* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithRenderTexture LayerWRTexture;
	typedef LayerWithRenderTexture LWRT;
}
