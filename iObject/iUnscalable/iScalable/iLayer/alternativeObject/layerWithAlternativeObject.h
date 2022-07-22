#pragma once
#include "../iLayer.h"

namespace ui {
	class LayerWithAlternativeObject : public ILayer {
	protected:
		IScalable* topObject;
		IScalable* bottomObject;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
	
	public:
		LayerWithAlternativeObject(IScalable* topObject, IScalable* bottomObject, sf::Vector2f minimumSize = {});
		
		~LayerWithAlternativeObject() override;
		
		void draw() override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithAlternativeObject* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithAlternativeObject LayerWAObject;
	typedef LayerWithAlternativeObject LWAO;
}