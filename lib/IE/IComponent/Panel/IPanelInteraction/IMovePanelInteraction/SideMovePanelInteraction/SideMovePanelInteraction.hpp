#pragma once

#include "../IMovePanelInteraction.hpp"
#include "../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class SideMovePanelInteraction : public BasePanelInteraction, public IMovePanelInteraction {
	public:
		SideMovePanelInteraction(float coefficient, float offset, bool horizontal, bool atStart = false);
		
		bool getAtStart() override;
		
		void move(sf::Vector2i mousePosition) override;
		
		SideMovePanelInteraction* copy() override;
	
	protected:
		float coefficient;
		float offset;
		bool horizontal;
		bool atStart;
	};
	
	template<>
	struct DecodePointer<SideMovePanelInteraction> {
		static bool decodePointer(const YAML::Node& node, SideMovePanelInteraction*& sideMovePanelInteraction);
	};
}
