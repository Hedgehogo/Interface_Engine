#pragma once

#include "../IPanelTrigger.hpp"

namespace ie {
	class IHidePanelTrigger : public virtual IPanelTrigger {
	public:
		struct Make : public virtual IPanelTrigger::Make {
			auto make(PanelActionInitInfo init_info) -> IHidePanelTrigger* override = 0;
		};
		
		auto get_priority() const -> Priority override;
	};
}
