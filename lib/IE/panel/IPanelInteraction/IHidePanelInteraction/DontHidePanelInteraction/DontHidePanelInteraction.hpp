#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"
#include "../IHidePanelInteraction.hpp"

namespace ie {
	class DontHidePanelInteraction : public BasicEmptyInteraction<Panel&>, public virtual IHidePanelInteraction {
	public:
		struct Make : public virtual IHidePanelInteraction::Make {
			DontHidePanelInteraction* make(PanelActionInitInfo init_info) override;
		};
		
		DontHidePanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		DontHidePanelInteraction() = default;
		
		void set_panel(Panel&) override;
	};
}

template<>
struct ieml::Decode<char, ie::DontHidePanelInteraction::Make> {
	static orl::Option<ie::DontHidePanelInteraction::Make> decode(ieml::Node const& node);
};
