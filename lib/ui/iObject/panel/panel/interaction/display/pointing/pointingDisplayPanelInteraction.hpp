#pragma once
#include "../displayPanelInteraction.hpp"
#include "../../general/panelInteraction.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class PointingDisplayPanelInteraction : public DisplayPanelInteraction, public PanelInteraction {
	public:
		PointingDisplayPanelInteraction();
		
		void start(sf::Vector2i mousePosition) override;
		
		bool update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		PointingDisplayPanelInteraction* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, PointingDisplayPanelInteraction *&pointingDisplayPanelInteraction);
}
