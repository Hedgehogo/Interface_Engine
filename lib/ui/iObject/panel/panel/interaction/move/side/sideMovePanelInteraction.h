#pragma once
#include "../movePanelInteraction.h"

namespace ui {
	class SideMovePanelInteraction : public MovePanelInteraction, public PanelInteraction {
	protected:
		float coefficient;
		float offset;
		bool horizontal;
	
	public:
		SideMovePanelInteraction(float coefficient, float offset, bool horizontal, bool atStart = false);
		
		void move(sf::Vector2i mousePosition) override;
		
		SideMovePanelInteraction* copy() override;

        static SideMovePanelInteraction* createFromYaml(const YAML::Node &node);
	};
}
