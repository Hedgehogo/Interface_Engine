#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../../../ClickPanelInteraction/PanelAction/PanelAction.hpp"

namespace ie {
	class DisplayPanelAction : public PanelAction {
	public:
		struct Make : public virtual PanelAction::Make {
			auto make(PanelActionInitInfo init_info) -> DisplayPanelAction* override;
		};
		
		DisplayPanelAction(Make&& make, PanelActionInitInfo init_info);
		
	protected:
		auto start_pressed() -> void override;
		
		auto while_pressed() -> void override;
		
		auto stop_pressed() -> void override;
		
		auto while_not_pressed() -> void override;
	};
}

template<>
struct ieml::Decode<char, ie::DisplayPanelAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::DisplayPanelAction::Make>;
};
