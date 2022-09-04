#pragma once
#include "../hidePanelInteraction.hpp"
#include "../../general/panelInteraction.hpp"

namespace ui {
	class PointingHidePanelInteraction : public HidePanelInteraction, public PanelInteraction {
	protected:
		bool onlyOnParent;
		
	public:
		PointingHidePanelInteraction(bool onlyOnParent = false);
		
		void start(sf::Vector2i mousePosition) override;
		
		bool update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		PointingHidePanelInteraction* copy() override;

        static PointingHidePanelInteraction* createFromYaml(const YAML::Node &node);
	};
}
