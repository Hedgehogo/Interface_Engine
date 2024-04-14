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
			
			auto make(PanelActionInitInfo init_info) -> SideMovePanelInteraction* override;
		};
		
		SideMovePanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		auto get_at_start() -> bool override;
		
		auto move(sf::Vector2i offset) -> void override;
		
	protected:
		float coefficient_;
		float offset_;
		bool horizontal_;
		bool at_start_;
	};
}

template<>
struct ieml::Decode<char, ie::SideMovePanelInteraction::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::SideMovePanelInteraction::Make>;
};
