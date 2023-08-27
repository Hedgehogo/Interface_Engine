#pragma once

#include "../IHidePanelInteraction.hpp"
#include "../../BasePanelInteraction/BasePanelInteraction.hpp"
#include "../../../../../Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	class PointingHidePanelInteraction : public BasePanelInteraction, public IHidePanelInteraction {
	public:
		struct Make : public IHidePanelInteraction::Make {
			bool onlyOnParent = false;
			
			Make(bool onlyOnParent = false);
			
			PointingHidePanelInteraction* make(PanelActionInitInfo initInfo) override;
		};
		
		PointingHidePanelInteraction(Make&& make, PanelActionInitInfo initInfo);
		
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
