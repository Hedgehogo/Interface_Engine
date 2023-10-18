#pragma once

#include "../IMovePanelInteraction.hpp"
#include "IE/interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"

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
		
		void init(PanelActionInitInfo) override;
		
		void set_panel(Panel&) override;
		
		DontMovePanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<DontMovePanelInteraction> {
		static bool decode_pointer(const YAML::Node&, DontMovePanelInteraction*& dont_move_panel_interaction);
	};
}