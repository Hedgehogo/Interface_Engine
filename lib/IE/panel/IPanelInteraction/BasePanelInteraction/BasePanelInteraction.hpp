#pragma once

#include "../IPanelInteraction.hpp"

namespace ie {
	class BasePanelInteraction : public virtual IPanelInteraction {
	public:
		BasePanelInteraction(PanelActionInitInfo init_info);
		
		auto set_panel(Panel& panel) -> void override;
		
	protected:
		Panel* panel_;
		IPanelManager* panel_manager_;
	};
}
