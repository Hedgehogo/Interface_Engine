#pragma once

#include "../iSizing2.hpp"
#include "../../sizing/iSizing.hpp"

namespace ui {
	class Sizing2 : public ISizing2 {
	protected:
		sf::RenderTarget* renderTarget;
		ISizing* horizontal;
		ISizing* vertical;
		
		void copy(Sizing2* sizing2);
	
	public:
		Sizing2(ISizing* horizontal, ISizing* vertical);
		
		Sizing2(bool relativeParent);
		
		Sizing2(sf::Vector2f constSize);
		
		Sizing2(sf::Vector2f coefficient, sf::Vector2f addition, bool relativeTarget = false);
		
		Sizing2(sf::Vector2f targetCoefficient, sf::Vector2f parentCoefficient, sf::Vector2f addition);
		
		~Sizing2() override;
		
		void init(sf::RenderTarget& renderTarget, sf::Vector2f normalSize) override;
		
		sf::Vector2f findSize(sf::Vector2f parentSize) override;
		
		sf::Vector2f getParentSize(sf::Vector2f objectSize) override;
		
		Sizing2* copy() override;
	};
	
	template<>
	struct DecodePointer<Sizing2> {
		static bool decodePointer(const YAML::Node& node, Sizing2*& sizing2);
	};
}
