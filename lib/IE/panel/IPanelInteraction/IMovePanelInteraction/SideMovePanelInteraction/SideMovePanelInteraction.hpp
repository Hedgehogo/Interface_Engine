#pragma once

#include "../IMovePanelInteraction.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	class SideMovePanelInteraction : public BasePanelInteraction, public virtual IMovePanelInteraction {
	public:
		struct Make : public virtual IMovePanelInteraction::Make {
			float coefficient;
			float offset;
			bool horizontal;
			bool at_start = false;
			
			Make(float coefficient, float offset, bool horizontal, bool at_start = false);
			
			SideMovePanelInteraction* make(PanelActionInitInfo init_info) override;
		};
		
		SideMovePanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		SideMovePanelInteraction(float coefficient, float offset, bool horizontal, bool at_start = false);
		
		bool get_at_start() override;
		
		void move(sf::Vector2i mouse_position) override;
		
		SideMovePanelInteraction* copy() override;
	
	protected:
		float coefficient_;
		float offset_;
		bool horizontal_;
		bool at_start_;
	};
	
	template<>
	struct DecodePointer<SideMovePanelInteraction> {
		static bool decode_pointer(const YAML::Node& node, SideMovePanelInteraction*& side_move_panel_interaction);
	};
}