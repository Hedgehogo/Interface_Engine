#pragma once
#include "../layer.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"

namespace ui {
	class LayerWithRenderTexture : public Layer, public LayoutWithObject, public IDrawable {
	protected:
		InteractionManager* interactionManager;
		DrawManager drawManager;
		sf::RenderTarget* renderTarget;
		sf::RenderTexture renderTexture;
        sf::View view;
		sf::Sprite sprite;
		bool optimize;
		bool active;
		
		void copy(LayerWithRenderTexture* layerWithRenderTexture);
		
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		LayerWithRenderTexture(IScalable *object, bool optimize = true, sf::Vector2f minSize = {});
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		LayerWithRenderTexture* copy() override;
		
		static LayerWithRenderTexture* createFromYaml(const YAML::Node &node);
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithRenderTexture LayerWRTexture;
	typedef LayerWithRenderTexture LWRT;
}
