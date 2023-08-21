#pragma once

#include "../IMovePanelInteraction.hpp"
#include "../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class CoefficientMovePanelInteraction : public BasePanelInteraction, public IMovePanelInteraction {
	public:
		CoefficientMovePanelInteraction(sf::Vector2f coefficient, sf::Vector2f offset, bool atStart = false);
		
		bool getAtStart() override;
		
		void move(sf::Vector2i mousePosition) override;
		
		CoefficientMovePanelInteraction* copy() override;
	
	protected:
		sf::Vector2f coefficient;
		sf::Vector2f offset;
		bool atStart;
	};
	
	template<>
	struct DecodePointer<CoefficientMovePanelInteraction> {
		static bool decodePointer(const YAML::Node& node, CoefficientMovePanelInteraction*& coefficientMovePanelInteraction);
	};
}
