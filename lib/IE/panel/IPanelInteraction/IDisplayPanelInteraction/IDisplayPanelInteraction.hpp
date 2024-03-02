#pragma once

#include "../IPanelInteraction.hpp"

namespace ie {
	class IDisplayPanelInteraction : public virtual IPanelInteraction {
	public:
		struct Make : public virtual IPanelInteraction::Make {
			auto make(PanelActionInitInfo init_info) -> IDisplayPanelInteraction* override = 0;
		};
	};
}