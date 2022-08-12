#pragma once
#include "../basePositioning2.hpp"

namespace ui {
	class Positioning2 : public BasePositioning2 {
	protected:
		sf::RenderTarget* renderTarget;
		Positioning* horizontal;
		Positioning* vertical;
		
		void copy(Positioning2* positioning2);
	
	public:
		Positioning2(Positioning* horizontal, Positioning* vertical);
		
		Positioning2(sf::Vector2f coefficient, sf::Vector2f offset = {}, bool relativeTarget = false);
		
		Positioning2(Location2 parentLocation, Location2 objectLocation, sf::Vector2f offset = {});
		
		Positioning2(sf::Vector2f coefficient, sf::Vector2f objectCoefficient, sf::Vector2f offset, bool relativeTarget = false);
		
		~Positioning2() override;
		
		void init(sf::RenderTarget& renderTarget) override;
		
		sf::Vector2f findPosition(sf::Vector2f parentPosition, sf::Vector2f parentSize, sf::Vector2f objectSize) override;
		
		Positioning2* copy() override;
		
		static Positioning2* createFromYaml(const YAML::Node &node);
	};
}
