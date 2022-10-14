#pragma once
#include "event/displayPanelEvent.h"
#include "../../click/clickPanelInteraction.hpp"

namespace ui {
	class ClickDisplayPanelInteraction : public ClickPanelInteraction, public DisplayPanelInteraction {
	public:
		explicit ClickDisplayPanelInteraction(KeyHandler::Key button);
	
	protected:
		ClickDisplayPanelInteraction(DisplayPanelEvent* displayPanelEvent, KeyHandler::Key button);
		
		void start(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
	
	public:
		ClickDisplayPanelInteraction* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, ClickDisplayPanelInteraction *&clickDisplayPanelInteraction);
}
