#pragma once

#include "../IMovePanelInteraction.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"

namespace ie {
	class CoefficientMovePanelInteraction : public BasePanelInteraction, public virtual IMovePanelInteraction {
	public:
		struct Make : public virtual IMovePanelInteraction::Make {
			sf::Vector2f coefficient;
			sf::Vector2f offset;
			bool atStart = false;
			
			Make(sf::Vector2f coefficient, sf::Vector2f offset, bool atStart = false);
			
			CoefficientMovePanelInteraction* make(PanelActionInitInfo initInfo) override;
		};
		
		CoefficientMovePanelInteraction(Make&& make, PanelActionInitInfo initInfo);
		
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