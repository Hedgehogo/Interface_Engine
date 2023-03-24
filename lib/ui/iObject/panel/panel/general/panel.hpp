#pragma once

#include "../../manager/general/panelManager.hpp"

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
		void init(InitInfo initInfo) override;
		
		Panel(IScalable *object, HidePanelInteraction *hideInteraction, MovePanelInteraction *moveInteraction, ISizing2 *sizing, IPositioning2 *positioning, bool displayed = false);
		
		Panel(IScalable *object, HidePanelInteraction *hideInteraction, ISizing2 *sizing, IPositioning2 *positioning, bool displayed = false);
		
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
	
	bool convertPointer(const YAML::Node &node, Panel *&panel);
}
