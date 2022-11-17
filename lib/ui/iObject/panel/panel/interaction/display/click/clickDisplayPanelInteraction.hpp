#pragma once
#include "event/displayPanelEvent.hpp"
#include "../../click/clickPanelInteraction.hpp"

namespace ui {
	class ClickDisplayPanelInteraction : public ClickPanelInteraction, public DisplayPanelInteraction {
	public:
		explicit ClickDisplayPanelInteraction(Key key);
	
	protected:
		ClickDisplayPanelInteraction(DisplayPanelEvent* displayPanelEvent, Key key);
		
		void start(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
	
	public:
		ClickDisplayPanelInteraction* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, ClickDisplayPanelInteraction *&clickDisplayPanelInteraction);
}
