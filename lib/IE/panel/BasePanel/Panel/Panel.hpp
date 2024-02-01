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
		
		void set_displayed() override;
		
		bool is_independent() override;
		
		bool is_free() override;
		
		bool in_const_panels(sf::Vector2f point_position);
		
		void draw() override;
		
		void update() override;
		
		bool update_interactions(sf::Vector2f mouse_position, bool active) override;
		
	protected:
		PanelManager panel_manager_;
		InteractionManager* interaction_manager_;
		BoxPtr<IHidePanelInteraction> hide_interaction_;
		BoxPtr<IMovePanelInteraction> move_interaction_;
	};
}

template<>
struct ieml::Decode<char, ie::Panel::Make> {
	static orl::Option<ie::Panel::Make> decode(ieml::Node const& node);
};
