#pragma once

#include "IE/utils/bool/ActiveTracker/ActiveTracker.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../../../ClickPanelInteraction/PanelAction/PanelAction.hpp"

namespace ie {
	class DisplayPanelAction : public PanelAction {
	public:
		struct Make : public virtual PanelAction::Make {
			auto make(PanelActionInitInfo init_info) -> DisplayPanelAction* override;
		};
		
		DisplayPanelAction(Make&& make, PanelActionInitInfo init_info);
		
		auto update(orl::Option<Touch> touch) -> void override;
		
	protected:
		ActiveTracker tracker_;
	};
}

template<>
struct ieml::Decode<char, ie::DisplayPanelAction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::DisplayPanelAction::Make>;
};
