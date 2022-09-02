#pragma once
#include "../movePanelInteraction.hpp"
#include "../../../../../../interaction/iInteraction/empty/emptyInteraction.hpp"

namespace ui {
	class DontMovePanelInteraction : public MovePanelInteraction {
	public:
		DontMovePanelInteraction();
		
		void move(sf::Vector2i mousePosition) override;
		
		void start(sf::Vector2i mousePosition) override;
		
		bool update(sf::Vector2i mousePosition) override;
		
		void init(Panel& panel, PanelManager& panelManager) override;
		
		void setPanel(Panel& panel) override;
		
		DontMovePanelInteraction* copy() override;

        static DontMovePanelInteraction* createFromYaml(const YAML::Node &node);
	};
}
