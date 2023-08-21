#pragma once

#include "DisplayPanelEvent/DisplayPanelEvent.hpp"
#include "../../ClickPanelInteraction/ClickPanelInteraction.hpp"

namespace ui {
	class ClickDisplayPanelInteraction : public ClickPanelInteraction, public IDisplayPanelInteraction {
	public:
		explicit ClickDisplayPanelInteraction(Key key);
		
		void start(sf::Vector2i) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		ClickDisplayPanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<ClickDisplayPanelInteraction> {
		static bool decodePointer(const YAML::Node& node, ClickDisplayPanelInteraction*& clickDisplayPanelInteraction);
	};
}
