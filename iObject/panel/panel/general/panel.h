#pragma once
#include "../basePanel.h"
#include "../../panelManager/panelManager.h"

namespace ui {
	class HidePanelInteraction;
	class Panel : public BasePanel {
	protected:
		PanelManager panelManager;
		InteractionManager* interactionManager;
		HidePanelInteraction* interaction;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		void copy(Panel* panel);
		
	public:
		Panel(IFlat *object, HidePanelInteraction *interaction, Sizing2* sizing, Positioning2* positioning, bool displayed = false);
		
		~Panel() override;
		
		virtual void setDisplayed();
		
		bool isIndependent() override;
		
		bool isFree() override;
		
		bool inConstPanels(sf::Vector2f pointPosition);
		
		void draw() override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition, bool active) override;
		
		Panel* copy() override;
	};
}
