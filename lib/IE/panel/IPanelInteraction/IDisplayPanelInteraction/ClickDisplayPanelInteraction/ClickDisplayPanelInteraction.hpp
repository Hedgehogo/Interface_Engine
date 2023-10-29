#pragma once

#include "DisplayPanelAction/DisplayPanelAction.hpp"
#include "../../ClickPanelInteraction/ClickPanelInteraction.hpp"

namespace ie {
	class ClickDisplayPanelInteraction : public ClickPanelInteraction, public virtual IDisplayPanelInteraction {
	public:
		struct Make : public virtual IDisplayPanelInteraction::Make {
			Key key;
			
			Make(Key key);
			
			ClickDisplayPanelInteraction* make(PanelActionInitInfo init_info) override;
		};
		
		ClickDisplayPanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		explicit ClickDisplayPanelInteraction(Key key);
		
		void start(sf::Vector2i) override;
		
		void finish(sf::Vector2i mouse_position) override;
		
		ClickDisplayPanelInteraction* copy() override;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<ClickDisplayPanelInteraction> {
		static bool decode_pointer(const YAML::Node& node, ClickDisplayPanelInteraction*& click_display_panel_interaction);
	};
	*/
}