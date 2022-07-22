#pragma once
#include "../iLayer.h"
#include "../../../../panel/panel/const/constPanel.h"
#include "../../../../layout/object/layoutWithObject.h"

namespace ui {
	class LayerWithPanel : public ILayer, public LayoutWithObject {
	protected:
		ConstPanel* panel;
		
	public:
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		LayerWithPanel(ConstPanel* panel, IScalable* object, sf::Vector2f minSize = {});
		
		~LayerWithPanel() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithPanel* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithPanel LayerWPanel;
	typedef LayerWithPanel LWP;
}
