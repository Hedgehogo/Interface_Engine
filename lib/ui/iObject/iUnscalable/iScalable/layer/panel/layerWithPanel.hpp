#pragma once
#include "../layer.hpp"
#include "../../../../panel/panel/const/constPanel.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"

namespace ui {
	class LayerWithPanel : public Layer, public LayoutWithObject {
	protected:
		ConstPanel* panel;
		
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, IPanelManager &panelManager) override;
		
		LayerWithPanel(ConstPanel* panel, IScalable* object, sf::Vector2f minSize = {});
		
		~LayerWithPanel() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithPanel* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	bool convertPointer(const YAML::Node &node, LayerWithPanel *&layerWithPanel);
	
	typedef LayerWithPanel LayerWPanel;
	typedef LayerWithPanel LWP;
}
