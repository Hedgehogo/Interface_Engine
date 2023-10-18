#pragma once

#include "../../IPanelManager/PanelManager/PanelManager.hpp"
#include "../../IPanelInteraction/IHidePanelInteraction/IHidePanelInteraction.hpp"
#include "../../IPanelInteraction/IMovePanelInteraction/IMovePanelInteraction.hpp"

namespace ie {
	class Panel : public BasePanel {
	public:
		struct Make : public virtual BasePanel::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IHidePanelInteraction::Make> hide_interaction;
			BoxPtr<IMovePanelInteraction::Make> move_interaction;
			BoxPtr<ISizing2::Make> sizing;
			BoxPtr<IPositioning2::Make> positioning;
			bool displayed = false;
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				BoxPtr<IHidePanelInteraction::Make> hide_interaction,
				BoxPtr<IMovePanelInteraction::Make> move_interaction,
				BoxPtr<ISizing2::Make> sizing,
				BoxPtr<IPositioning2::Make> positioning,
				bool displayed = false
			);
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				BoxPtr<IHidePanelInteraction::Make> hide_interaction,
				BoxPtr<ISizing2::Make> sizing,
				BoxPtr<IPositioning2::Make> positioning,
				bool displayed = false
			);
			
			Panel* make(InitInfo init_info) override;
		};
		
		Panel(Make&& make, InitInfo init_info);
		
		Panel(
			BoxPtr<IScalable>&& object,
			BoxPtr<IHidePanelInteraction> hide_interaction,
			BoxPtr<IMovePanelInteraction> move_interaction,
			BoxPtr<ISizing2> sizing,
			BoxPtr<IPositioning2> positioning,
			bool displayed = false
		);
		
		Panel(
			BoxPtr<IScalable>&& object,
			BoxPtr<IHidePanelInteraction> hide_interaction,
			BoxPtr<ISizing2> sizing,
			BoxPtr<IPositioning2> positioning,
			bool displayed = false
		);
		
		Panel(const Panel& other);
		
		void init(InitInfo init_info) override;
		
		void set_displayed() override;
		
		bool is_independent() override;
		
		bool is_free() override;
		
		bool in_const_panels(sf::Vector2f point_position);
		
		void draw() override;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position, bool active) override;
		
		Panel* copy() override;
	
	protected:
		PanelManager panel_manager;
		InteractionManager* interaction_manager;
		BoxPtr<IHidePanelInteraction> hide_interaction;
		BoxPtr<IMovePanelInteraction> move_interaction;
	};
	
	template<>
	struct DecodePointer<Panel> {
		static bool decode_pointer(const YAML::Node& node, Panel*& panel);
	};
}
