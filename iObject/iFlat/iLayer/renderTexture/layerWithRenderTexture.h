#pragma once
#include "../iLayer.h"

namespace ui {
	class LayerWithRenderTexture : public ILayer {
	protected:
		IFlat* object;
		sf::RenderTarget* renderTarget;
		sf::RenderTexture renderTexture;
		sf::Sprite sprite;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		void copy(LayerWithRenderTexture* layerWithRenderTexture);
		
	public:
		LayerWithRenderTexture(IFlat* object, sf::Vector2f minSize = {});
	
		~LayerWithRenderTexture() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithRenderTexture* copy() override;
	};
}
