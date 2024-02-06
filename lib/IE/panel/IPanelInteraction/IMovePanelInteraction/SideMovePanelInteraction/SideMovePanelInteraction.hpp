#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../IMovePanelInteraction.hpp"

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
		
		bool get_at_start() override;
		
		void move(sf::Vector2i mouse_position) override;
		
	protected:
		float coefficient_;
		float offset_;
		bool horizontal_;
		bool at_start_;
	};
}

template<>
struct ieml::Decode<char, ie::SideMovePanelInteraction::Make> {
	static orl::Option<ie::SideMovePanelInteraction::Make> decode(ieml::Node const& node);
};
