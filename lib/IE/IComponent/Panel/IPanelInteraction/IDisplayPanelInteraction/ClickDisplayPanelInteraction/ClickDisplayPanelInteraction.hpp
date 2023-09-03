#pragma once

#include "IE/IComponent/Panel/IPanelInteraction/IDisplayPanelInteraction/ClickDisplayPanelInteraction/DisplayPanelAction/DisplayPanelAction.hpp"
#include "../../ClickPanelInteraction/ClickPanelInteraction.hpp"

namespace ie {
	class ClickDisplayPanelInteraction : public ClickPanelInteraction, public virtual IDisplayPanelInteraction {
	public:
		struct Make : public virtual IDisplayPanelInteraction::Make {
			Key key;
			
			Make(Key key);
			
			ClickDisplayPanelInteraction* make(PanelActionInitInfo initInfo) override;
		};
		
		ClickDisplayPanelInteraction(Make&& make, PanelActionInitInfo initInfo);
		
		explicit ClickDisplayPanelInteraction(Key key);
		
		void start(sf::Vector2i) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		ClickDisplayPanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<ClickDisplayPanelInteraction> {
		static bool decodePointer(const YAML::Node& node, ClickDisplayPanelInteraction*& clickDisplayPanelInteraction);
	};
}
