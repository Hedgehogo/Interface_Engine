#pragma once

#include "../IHidePanelInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"

namespace ie {
	class DontHidePanelInteraction : public BasicEmptyInteraction<Panel&>, public IHidePanelInteraction {
	public:
		DontHidePanelInteraction() = default;
		
		void init(PanelInteractionInitInfo initInfo) override;
		
		void setPanel(Panel&) override;
		
		DontHidePanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<DontHidePanelInteraction> {
		static bool decodePointer(const YAML::Node&, DontHidePanelInteraction*& dontHidePanelInteraction);
	};
}
