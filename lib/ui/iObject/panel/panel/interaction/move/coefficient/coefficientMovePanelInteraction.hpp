#pragma once
#include "../movePanelInteraction.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class CoefficientMovePanelInteraction : public MovePanelInteraction, public PanelInteraction {
	protected:
		sf::Vector2f coefficient;
		sf::Vector2f offset;
	
	public:
		CoefficientMovePanelInteraction(sf::Vector2f coefficient, sf::Vector2f offset, bool atStart = false);
		
		void move(sf::Vector2i mousePosition) override;
		
		CoefficientMovePanelInteraction* copy() override;
	};
	
	
	template<>
	struct DecodePointer<CoefficientMovePanelInteraction> {
		static bool decodePointer(const YAML::Node &node, CoefficientMovePanelInteraction *&coefficientMovePanelInteraction);
	};
}
