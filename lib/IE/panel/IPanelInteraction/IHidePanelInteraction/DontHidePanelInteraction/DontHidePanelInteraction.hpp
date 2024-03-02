#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"
#include "../IHidePanelInteraction.hpp"

namespace ie {
	class DontHidePanelInteraction : public BasicEmptyInteraction<Panel&>, public virtual IHidePanelInteraction {
	public:
		struct Make : public virtual IHidePanelInteraction::Make {
			auto make(PanelActionInitInfo init_info) -> DontHidePanelInteraction* override;
		};
		
		DontHidePanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		DontHidePanelInteraction() = default;
		
		auto set_panel(Panel&) -> void override;
	};
}

template<>
struct ieml::Decode<char, ie::DontHidePanelInteraction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::DontHidePanelInteraction::Make>;
};
