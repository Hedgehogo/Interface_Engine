#pragma once

#include "../IPanelTrigger.hpp"

namespace ie {
	class IDisplayPanelTrigger : public virtual IPanelTrigger {
	public:
		struct Make : public virtual IPanelTrigger::Make {
			auto make(PanelActionInitInfo init_info) -> IDisplayPanelTrigger* override = 0;
		};
	};
}