#pragma once

#include "../IHidePanelInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"

namespace ui {
	class DontHidePanelInteraction : public EmptyInteraction, public IHidePanelInteraction {
	public:
		DontHidePanelInteraction() = default;
		
		void init(PanelInteractionInitInfo) override;
		
		void setPanel(Panel&) override;
		
		DontHidePanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<DontHidePanelInteraction> {
		static bool decodePointer(const YAML::Node&, DontHidePanelInteraction*& dontHidePanelInteraction);
	};
}
