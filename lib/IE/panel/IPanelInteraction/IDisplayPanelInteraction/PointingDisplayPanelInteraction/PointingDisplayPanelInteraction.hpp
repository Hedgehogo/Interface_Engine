#pragma once

#include "../IDisplayPanelInteraction.hpp"
#include "../../BasePanelInteraction/BasePanelInteraction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	class PointingDisplayPanelInteraction : public BasePanelInteraction, public virtual IDisplayPanelInteraction {
	public:
		struct Make : public virtual IDisplayPanelInteraction::Make {
			PointingDisplayPanelInteraction* make(PanelActionInitInfo init_info) override;
		};
		
		PointingDisplayPanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		PointingDisplayPanelInteraction() = default;
		
		void start(sf::Vector2i mouse_position) override;
		
		void update(sf::Vector2i mouse_position) override;
		
		void finish(sf::Vector2i mouse_position) override;
		
		PointingDisplayPanelInteraction* copy() override;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<PointingDisplayPanelInteraction> {
		static bool decode_pointer(const YAML::Node&, PointingDisplayPanelInteraction*& pointing_display_panel_interaction);
	};
	*/
}