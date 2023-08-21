#pragma once

#include "../IMovePanelInteraction.hpp"
#include "../../../../../Interaction/IInteraction/EmptyInteraction/EmptyInteraction.hpp"

namespace ui {
	class DontMovePanelInteraction : public IMovePanelInteraction {
	public:
		DontMovePanelInteraction();
		
		bool getAtStart() override;
		
		void move(sf::Vector2i) override;
		
		void start(sf::Vector2i) override;
		
		void update(sf::Vector2i) override;
		
		void init(PanelInteractionInitInfo) override;
		
		void setPanel(Panel&) override;
		
		DontMovePanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<DontMovePanelInteraction> {
		static bool decodePointer(const YAML::Node&, DontMovePanelInteraction*& dontMovePanelInteraction);
	};
}
