#pragma once
#include "../../enums/enums.h"
#include "../iFlat/iFlat.h"
#include "../layout/layout.h"
#include "../../sizingAndPositioning/sizing2/sizing2.h"
#include "../../sizingAndPositioning/positioning2/positioning2.h"

namespace ui {
	class HidePanelInteraction;
	class Panel : public Layout {
	protected:
		IFlat *object;
		InteractionManager* interactionManager;
		HidePanelInteraction* interaction;
		Sizing2* sizing;
		Positioning2* positioning;
		bool parentProcessed;
		bool oldDisplayed;
		bool displayed;
		bool active;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void copy(Panel* panel);
	
	public:
		Panel(IFlat *object, HidePanelInteraction *interaction, Sizing2* sizing, Positioning2* positioning, bool displayed = false);
		
		~Panel() override;
		
		void setParentProcessed(bool parentProcessed);
		
		bool getParentProcessed();
		
		bool isActive();
		
		bool inPanel(sf::Vector2f position);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		void update() override;
		
		virtual bool updateInteractions(bool active, sf::Vector2f mousePosition);
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		Panel* copy() override;
	};
}
