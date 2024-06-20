#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/event/PointerTracker/PointerTracker.hpp"
#include "../IMovePanelInteraction.hpp"

namespace ie {
	class SideMovePanelInteraction : public virtual IMovePanelInteraction {
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
		
		auto set_panel(Panel& panel) -> void override;
		
		auto move(sf::Vector2i offset) -> void override;
		
		auto start() -> void override;
		
		auto handle_event(Event event) -> bool override;
		
		auto update() -> void override;
		
		auto finish() -> void override;
	
	protected:
		Panel* panel_;
		IPanelManager* panel_manager_;
		EventHandler* event_handler_;
		PointerTracker tracker_;
		bool active_;
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
