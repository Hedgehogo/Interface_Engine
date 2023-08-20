#pragma once

#include "../iHidePanelInteraction.hpp"
#include "../../general/panelInteraction.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class PointingHidePanelInteraction : public PanelInteraction, public IHidePanelInteraction {
	public:
		PointingHidePanelInteraction(bool onlyOnParent = false);
		
		void start(sf::Vector2i mousePosition) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		void finish(sf::Vector2i mousePosition) override;
		
		PointingHidePanelInteraction* copy() override;
	
	protected:
		bool onlyOnParent;
	};
	
	template<>
	struct DecodePointer<PointingHidePanelInteraction> {
		static bool decodePointer(const YAML::Node& node, PointingHidePanelInteraction*& pointingHidePanelInteraction);
	};
}
