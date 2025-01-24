#pragma once

#include "../../IPanelManager/PanelManager/PanelManager.hpp"
#include "../../IPanelTrigger/IHidePanelTrigger/IHidePanelTrigger.hpp"
#include "../../IPanelTrigger/IMovePanelTrigger/IMovePanelTrigger.hpp"

namespace ie {
	class Panel : public BasePanel {
	public:
		struct Make : public virtual BasePanel::Make {
			BoxPtr<IScalable::Make> object;
			BoxPtr<IHidePanelTrigger::Make> hide_trigger;
			BoxPtr<IMovePanelTrigger::Make> move_trigger;
			BoxPtr<ISizing2::Make> sizing;
			BoxPtr<IPositioning2::Make> positioning;
			bool displayed = false;
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				BoxPtr<IHidePanelTrigger::Make> hide_trigger,
				BoxPtr<IMovePanelTrigger::Make> move_trigger,
				BoxPtr<ISizing2::Make> sizing,
				BoxPtr<IPositioning2::Make> positioning,
				bool displayed = false
			);
			
			Make(
				BoxPtr<IScalable::Make>&& object,
				BoxPtr<IHidePanelTrigger::Make> hide_trigger,
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
		
		auto handle_event(Event event, bool active) -> bool override;
		
	protected:
		PanelManager panel_manager_;
		TriggerManager* trigger_manager_;
		BoxPtr<IHidePanelTrigger> hide_trigger_;
		BoxPtr<IMovePanelTrigger> move_trigger_;
	};
}

template<>
struct ieml::Decode<char, ie::Panel::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Panel::Make>;
};
