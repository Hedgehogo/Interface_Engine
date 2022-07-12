#pragma once
#include "../iLayer.h"
#include "../../../panel/panel/const/constPanel.h"

namespace ui {
	class LayerWithPanel : public ILayer {
	protected:
		IFlat* object;
		ConstPanel* panel;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
	public:
		LayerWithPanel(IFlat* object, ConstPanel* panel, sf::Vector2f minSize = {});
		
		~LayerWithPanel() override;
		
		void draw() override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		LayerWithPanel* copy() override;
		
		void drawDebug(sf::RenderTarget &renderTarget, int indent, int indentAddition, uint hue, uint hueOffset) override;
	};
	
	typedef LayerWithPanel LayerWPanel;
	typedef LayerWithPanel LWP;
}
