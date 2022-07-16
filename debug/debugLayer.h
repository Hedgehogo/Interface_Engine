#pragma once
#include "../iObject/iFlat/iLayer/iLayer.h"

namespace ui {
	class DebugLayer : public ILayer {
	protected:
		IFlat* object;
		sf::RenderTarget* renderTarget;
		bool active;
		bool drawn;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
	public:
		DebugLayer(IFlat* object);
		
		~DebugLayer() override;
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		DebugLayer* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
}
