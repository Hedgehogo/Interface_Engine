#pragma once

#include "../IPanelInteraction.hpp"

namespace ie {
	class BasePanelInteraction : public virtual IPanelInteraction {
	public:
		BasePanelInteraction(PanelActionInitInfo init_info);
		
		void set_panel(Panel& panel) override;
		
	protected:
		Panel* panel_;
		IPanelManager* panel_manager_;
	};
}
