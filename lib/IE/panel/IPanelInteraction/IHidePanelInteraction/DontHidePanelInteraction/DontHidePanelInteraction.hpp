#pragma once

#include "../IHidePanelInteraction.hpp"
#include "IE/interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"

namespace ie {
	class DontHidePanelInteraction : public BasicEmptyInteraction<Panel&>, public virtual IHidePanelInteraction {
	public:
		struct Make : public virtual IHidePanelInteraction::Make {
			DontHidePanelInteraction* make(PanelActionInitInfo init_info) override;
		};
		
		DontHidePanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		DontHidePanelInteraction() = default;
		
		void init(PanelActionInitInfo init_info) override;
		
		void set_panel(Panel&) override;
		
		DontHidePanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<DontHidePanelInteraction> {
		static bool decode_pointer(const YAML::Node&, DontHidePanelInteraction*& dont_hide_panel_interaction);
	};
}