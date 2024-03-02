#pragma once

#include "../IPanelInteraction.hpp"

namespace ie {
	class IHidePanelInteraction : public virtual IPanelInteraction {
	public:
		struct Make : public virtual IPanelInteraction::Make {
			auto make(PanelActionInitInfo init_info) -> IHidePanelInteraction* override = 0;
		};
		
		auto get_priority() const -> Priority override;
	};
}
