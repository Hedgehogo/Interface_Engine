#pragma once
#include "../../../click/event/panelEvent.h"

namespace ui {
	class DisplayPanelEvent : public PanelEvent {
	protected:
		void startPressed   (sf::Vector2i) override;
		
		void whilePressed   (sf::Vector2i) override;
		
		void stopPressed    (sf::Vector2i) override;
		
		void whileNotPressed(sf::Vector2i) override;
	
	public:
		DisplayPanelEvent* copy() override;

        static DisplayPanelEvent* createFromYaml(const YAML::Node &node);
	};
}
