#pragma once

#include "../../manager/general/panelManager.hpp"

namespace ui {
	class HidePanelInteraction;
	
	class MovePanelInteraction;
	
	class Panel : public BasePanel {
	public:
		void init(InitInfo initInfo) override;
		
		Panel(
			BoxPtr<IScalable>&& object,
			BoxPtr<HidePanelInteraction> hideInteraction,
			BoxPtr<MovePanelInteraction> moveInteraction,
			BoxPtr<ISizing2> sizing,
			BoxPtr<IPositioning2> positioning,
			bool displayed = false
		);
		
		Panel(
			BoxPtr<IScalable>&& object,
			BoxPtr<HidePanelInteraction> hideInteraction,
			BoxPtr<ISizing2> sizing,
			BoxPtr<IPositioning2> positioning,
			bool displayed = false
		);
		
		Panel(const Panel& other);
		
		void setDisplayed() override;
		
		bool isIndependent() override;
		
		bool isFree() override;
		
		bool inConstPanels(sf::Vector2f pointPosition);
		
		void draw() override;
		
		void update() override;
		
		bool updateInteractions(sf::Vector2f mousePosition, bool active) override;
		
		Panel* copy() override;
	
	protected:
		PanelManager panelManager;
		InteractionManager* interactionManager;
		BoxPtr<HidePanelInteraction> hideInteraction;
		BoxPtr<MovePanelInteraction> moveInteraction;
	};
	
	template<>
	struct DecodePointer<Panel> {
		static bool decodePointer(const YAML::Node& node, Panel*& panel);
	};
}
