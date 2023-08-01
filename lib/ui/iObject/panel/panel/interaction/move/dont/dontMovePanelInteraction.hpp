#pragma once

#include "../iMovePanelInteraction.hpp"
#include "../../../../../../interaction/iInteraction/empty/emptyInteraction.hpp"

namespace ui {
	class DontMovePanelInteraction : public IMovePanelInteraction {
	public:
		DontMovePanelInteraction();
		
		bool getAtStart() override;
		
		void move(sf::Vector2i mousePosition) override;
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void init(PanelInteractionInitInfo panelInteractionInitInfo) override;
		
		void setPanel(Panel& panel) override;
		
		DontMovePanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<DontMovePanelInteraction> {
		static bool decodePointer(const YAML::Node& node, DontMovePanelInteraction*& dontMovePanelInteraction);
	};
}
