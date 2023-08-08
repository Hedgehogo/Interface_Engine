#pragma once

#include "../../manager/general/panelManager.hpp"

namespace ui {
	class IHidePanelInteraction;
	
	class IMovePanelInteraction;
	
	class Panel : public BasePanel {
	public:
		Panel(
			BoxPtr<IScalable>&& object,
			BoxPtr<IHidePanelInteraction> hideInteraction,
			BoxPtr<IMovePanelInteraction> moveInteraction,
			BoxPtr<ISizing2> sizing,
			BoxPtr<IPositioning2> positioning,
			bool displayed = false
		);
		
		Panel(
			BoxPtr<IScalable>&& object,
			BoxPtr<IHidePanelInteraction> hideInteraction,
			BoxPtr<ISizing2> sizing,
			BoxPtr<IPositioning2> positioning,
			bool displayed = false
		);
		
		Panel(const Panel& other);
		
		void init(InitInfo initInfo) override;
		
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
		BoxPtr<IHidePanelInteraction> hideInteraction;
		BoxPtr<IMovePanelInteraction> moveInteraction;
	};
	
	template<>
	struct DecodePointer<Panel> {
		static bool decodePointer(const YAML::Node& node, Panel*& panel);
	};
}
