#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"
#include "../IMovePanelInteraction.hpp"

namespace ie {
	class DontMovePanelInteraction : public virtual IMovePanelInteraction {
	public:
		struct Make : public virtual IMovePanelInteraction::Make {
			DontMovePanelInteraction* make(PanelActionInitInfo init_info) override;
		};
		
		DontMovePanelInteraction(Make&& make, PanelActionInitInfo init_info);
		
		DontMovePanelInteraction() = default;
		
		bool get_at_start() override;
		
		void move(sf::Vector2i) override;
		
		void start(sf::Vector2i) override;
		
		void update(sf::Vector2i) override;
		
		void set_panel(Panel&) override;
	};
}

template<>
struct ieml::Decode<char, ie::DontMovePanelInteraction::Make> {
	static orl::Option<ie::DontMovePanelInteraction::Make> decode(ieml::Node const& node);
};
