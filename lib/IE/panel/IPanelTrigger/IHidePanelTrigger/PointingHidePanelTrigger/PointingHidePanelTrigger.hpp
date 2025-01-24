#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IHidePanelTrigger.hpp"

namespace ie {
	class PointingHidePanelTrigger : public virtual IHidePanelTrigger {
	public:
		struct Make : public virtual IHidePanelTrigger::Make {
			bool only_on_parent = false;
			
			Make(bool only_on_parent = false);
			
			auto make(PanelActionInitInfo init_info) -> PointingHidePanelTrigger* override;
		};
		
		PointingHidePanelTrigger(Make&& make, PanelActionInitInfo init_info);
		
		auto set_panel(Panel& panel) -> void override;
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
		
	protected:
		Panel* panel_;
		IPanelManager* panel_manager_;
		bool only_on_parent_;
		bool active_;
	};
}

template<>
struct ieml::Decode<char, ie::PointingHidePanelTrigger::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::PointingHidePanelTrigger::Make>;
};
