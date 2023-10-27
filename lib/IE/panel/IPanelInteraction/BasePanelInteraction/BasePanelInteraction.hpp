#pragma once

#include "../IPanelInteraction.hpp"

namespace ie {
	class BasePanelInteraction : public virtual IPanelInteraction {
	public:
		BasePanelInteraction(PanelActionInitInfo init_info);
		
		BasePanelInteraction();
		
		void init(PanelActionInitInfo init_info) override;
		
		void set_panel(Panel& panel) override;
		
		BasePanelInteraction* copy() override = 0;
	
	protected:
		Panel* panel_;
		IPanelManager* panel_manager_;
	};
}
