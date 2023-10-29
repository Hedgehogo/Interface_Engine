#pragma once

#include "../IHidePanelInteraction.hpp"
#include "../../BasePanelInteraction/BasePanelInteraction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"

namespace ie {
	class PointingHidePanelInteraction : public BasePanelInteraction, public virtual IHidePanelInteraction {
	public:
		struct Make : public virtual IHidePanelInteraction::Make {
			bool only_on_parent = false;
			
			Make(bool only_on_parent = false);
			
			PointingHidePanelInteraction* make(PanelActionInitInfo init_info) override;
		};
		
		PointingHidePanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		PointingHidePanelInteraction(bool only_on_parent = false);
		
		void start(sf::Vector2i mouse_position) override;
		
		void update(sf::Vector2i mouse_position) override;
		
		void finish(sf::Vector2i mouse_position) override;
		
		PointingHidePanelInteraction* copy() override;
	
	protected:
		bool only_on_parent_;
	};
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<PointingHidePanelInteraction> {
		static bool decode_pointer(const YAML::Node& node, PointingHidePanelInteraction*& pointing_hide_panel_interaction);
	};
	*/
}