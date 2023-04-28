#pragma once

#include "../movePanelInteraction.hpp"
#include "../../../../../../interaction/iInteraction/empty/emptyInteraction.hpp"

namespace ui {
	class DontMovePanelInteraction : public MovePanelInteraction {
	public:
		DontMovePanelInteraction();
		
		void move(sf::Vector2i mousePosition) override;
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void init(Panel& panel, IPanelManager& panelManager) override;
		
		void setPanel(Panel& panel) override;
		
		DontMovePanelInteraction* copy() override;
	};
	
	
	template<>
	struct DecodePointer<DontMovePanelInteraction> {
		static bool decodePointer(const YAML::Node& node, DontMovePanelInteraction*& dontMovePanelInteraction);
	};
}
