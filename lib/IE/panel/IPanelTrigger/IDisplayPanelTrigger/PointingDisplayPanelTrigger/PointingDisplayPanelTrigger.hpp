#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IDisplayPanelTrigger.hpp"

namespace ie {
	class PointingDisplayPanelTrigger : public virtual IDisplayPanelTrigger {
	public:
		struct Make : public virtual IDisplayPanelTrigger::Make {
			auto make(PanelActionInitInfo init_info) -> PointingDisplayPanelTrigger* override;
		};
		
		PointingDisplayPanelTrigger(Make&& make, PanelActionInitInfo init_info);
		
		auto set_panel(Panel& panel) -> void override;
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
		
	protected:
		Panel* panel_;
		IPanelManager* panel_manager_;
	};
}

template<>
struct ieml::Decode<char, ie::PointingDisplayPanelTrigger::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::PointingDisplayPanelTrigger::Make>;
};
