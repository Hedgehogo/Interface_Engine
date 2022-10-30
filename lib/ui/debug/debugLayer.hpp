#pragma once
#include "../iObject/iUnscalable/iScalable/layer/layer.hpp"

namespace ui {
	class DebugLayer : public Layer, public IDrawable {
	protected:
		IScalable* object;
		sf::RenderTarget* renderTarget;
		bool active;
		bool drawn;
		
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;
		
	public:
		DebugLayer(IScalable* object);
		
		~DebugLayer() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		DebugLayer* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, DebugLayer *&debugLayer);
}
