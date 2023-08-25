#pragma once

#include "../IDisplayPanelInteraction.hpp"
#include "../../BasePanelInteraction/BasePanelInteraction.hpp"
#include "../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class PointingDisplayPanelInteraction : public BasePanelInteraction, public IDisplayPanelInteraction {
	public:
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		PointingDisplayPanelInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<PointingDisplayPanelInteraction> {
		static bool decodePointer(const YAML::Node&, PointingDisplayPanelInteraction*& pointingDisplayPanelInteraction);
	};
}
