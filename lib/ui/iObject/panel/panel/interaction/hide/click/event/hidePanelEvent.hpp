#pragma once
#include "../../../click/event/panelEvent.hpp"

namespace ui {
	class HidePanelEvent : public PanelEvent {
	protected:
		bool onlyOnParent;
		
		void startPressed   (sf::Vector2i mousePosition) override;
		
		void whilePressed   (sf::Vector2i mousePosition) override;
		
		void stopPressed    (sf::Vector2i mousePosition) override;
		
		void whileNotPressed(sf::Vector2i mousePosition) override;
		
	public:
		HidePanelEvent(bool onlyOnParent = false);
		
		HidePanelEvent* copy() override;

        static HidePanelEvent* createFromYaml(const YAML::Node &node);
	};
}
