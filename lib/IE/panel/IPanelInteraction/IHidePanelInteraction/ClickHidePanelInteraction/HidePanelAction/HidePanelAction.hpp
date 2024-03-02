#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../../../ClickPanelInteraction/PanelAction/PanelAction.hpp"

namespace ie {
	class HidePanelAction : public PanelAction {
	public:
		struct Make : public virtual PanelAction::Make {
			bool only_on_parent = false;
			
			Make(bool only_on_parent = false);
			
			auto make(PanelActionInitInfo init_info) -> HidePanelAction* override;
		};
		
		HidePanelAction(Make&& make, PanelActionInitInfo init_info);
		
	protected:
		auto start_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
		
		bool only_on_parent;
	};
}

template<>
struct ieml::Decode<char, ie::HidePanelAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::HidePanelAction::Make>;
};
