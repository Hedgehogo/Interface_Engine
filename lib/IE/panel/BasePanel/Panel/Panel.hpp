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
			
			auto make(InitInfo init_info) -> Panel* override;
		};
		
		Panel(Make&& make, InitInfo init_info);
		
		auto set_displayed() -> void override;
		
		auto is_independent() -> bool override;
		
		auto is_free() -> bool override;
		
		auto in_const_panels(sf::Vector2f point_position) -> bool;
		
		auto draw() -> void override;
		
		auto update() -> void override;
		
		auto update_interactions(sf::Vector2f mouse_position, bool active) -> bool override;
		
	protected:
		PanelManager panel_manager_;
		InteractionManager* interaction_manager_;
		BoxPtr<IHidePanelInteraction> hide_interaction_;
		BoxPtr<IMovePanelInteraction> move_interaction_;
	};
}

template<>
struct ieml::Decode<char, ie::Panel::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Panel::Make>;
};
