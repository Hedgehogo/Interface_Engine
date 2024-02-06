#pragma once

#include "../IPanelInteraction.hpp"

namespace ie {
	class IHidePanelInteraction : public virtual IPanelInteraction {
	public:
		struct Make : public virtual IPanelInteraction::Make {
			IHidePanelInteraction* make(PanelActionInitInfo init_info) override = 0;
		};
		
		Priority get_priority() const override;
	};
}
