#pragma once

#include "../movePanelInteraction.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class SideMovePanelInteraction : public MovePanelInteraction, public PanelInteraction {
	public:
		SideMovePanelInteraction(float coefficient, float offset, bool horizontal, bool atStart = false);
		
		void move(sf::Vector2i mousePosition) override;
		
		SideMovePanelInteraction* copy() override;
	
	protected:
		float coefficient;
		float offset;
		bool horizontal;
	};
	
	template<>
	struct DecodePointer<SideMovePanelInteraction> {
		static bool decodePointer(const YAML::Node& node, SideMovePanelInteraction*& sideMovePanelInteraction);
	};
}
