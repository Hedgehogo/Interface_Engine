#pragma once

#include "../IHidePanelInteraction.hpp"
#include "../../BasePanelInteraction/BasePanelInteraction.hpp"
#include "../../../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	class PointingHidePanelInteraction : public BasePanelInteraction, public IHidePanelInteraction {
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
