#pragma once

#include "../../IPanelManager/PanelManager/PanelManager.hpp"
#include "../../IPanelInteraction/IHidePanelInteraction/IHidePanelInteraction.hpp"
#include "../../IPanelInteraction/IMovePanelInteraction/IMovePanelInteraction.hpp"

namespace ie {
	class Panel : public BasePanel {
	public:
		struct Make : public virtual BasePanel::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IHidePanelInteraction::Make> hideInteraction;
			BoxPtr<IMovePanelInteraction::Make> moveInteraction;
			BoxPtr<ISizing2::Make> sizing;
			BoxPtr<IPositioning2::Make> positioning;
			bool displayed = false;
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				BoxPtr<IHidePanelInteraction::Make> hideInteraction,
				BoxPtr<IMovePanelInteraction::Make> moveInteraction,
				BoxPtr<ISizing2::Make> sizing,
				BoxPtr<IPositioning2::Make> positioning,
				bool displayed = false
			);
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				BoxPtr<IHidePanelInteraction::Make> hideInteraction,
				BoxPtr<ISizing2::Make> sizing,
				BoxPtr<IPositioning2::Make> positioning,
				bool displayed = false
			);
			
			Panel* make(InitInfo initInfo) override;
		};
		
		Panel(Make&& make, InitInfo initInfo);
		
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
