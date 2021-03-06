#pragma once
#include "../basePanel.h"
#include "../../panelManager/panelManager.h"

namespace ui {
	class HidePanelInteraction;
	class MovePanelInteraction;
	class Panel : public BasePanel {
	protected:
		PanelManager panelManager;
		InteractionManager* interactionManager;
		HidePanelInteraction* hideInteraction;
		MovePanelInteraction* moveInteraction;
		
		void copy(Panel* panel);
		
	public:
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		Panel(IScalable *object, HidePanelInteraction *hideInteraction, MovePanelInteraction *moveInteraction, Sizing2 *sizing, Positioning2 *positioning, bool displayed = false);
		
		Panel(IScalable *object, HidePanelInteraction *hideInteraction, Sizing2 *sizing, Positioning2 *positioning, bool displayed = false);
		
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
