#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
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
		
		auto update(orl::Option<Touch> touch) -> void override;
		
	protected:
		orl::Option<sf::Vector2f> pressing;
		bool only_on_parent_;
	};
}

template<>
struct ieml::Decode<char, ie::HidePanelAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::HidePanelAction::Make>;
};
