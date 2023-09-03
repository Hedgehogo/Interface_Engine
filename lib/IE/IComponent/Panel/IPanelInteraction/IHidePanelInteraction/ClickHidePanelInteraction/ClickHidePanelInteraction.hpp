#pragma once

#include "IE/IComponent/Panel/IPanelInteraction/IHidePanelInteraction/ClickHidePanelInteraction/HidePanelAction/HidePanelAction.hpp"
#include "../../ClickPanelInteraction/ClickPanelInteraction.hpp"

namespace ie {
	class ClickHidePanelInteraction : public ClickPanelInteraction, public virtual IHidePanelInteraction {
	public:
		struct Make : public virtual IHidePanelInteraction::Make {
			Key key;
			bool onlyOnParent = false;
			
			Make(Key key, bool onlyOnParent = false);
			
			ClickHidePanelInteraction* make(PanelActionInitInfo initInfo) override;
		};
		
		ClickHidePanelInteraction(Make&& make, PanelActionInitInfo initInfo);
		
		explicit ClickHidePanelInteraction(Key key, bool onlyOnParent = false);
		
		ClickHidePanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<ClickHidePanelInteraction> {
		static bool decodePointer(const YAML::Node& node, ClickHidePanelInteraction*& clickHidePanelInteraction);
	};
}
