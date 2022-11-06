#pragma once
#include "../onlyDrawable.hpp"
#include "../../../../../layout/layout.hpp"

namespace ui {
	class RoundedRectangle : public OnlyDrawable, public Layout {
	protected:
		sf::RectangleShape horizontalRectangle;
		sf::RectangleShape verticalRectangle;
		sf::CircleShape circle;
		float radius;
		
	public:
		RoundedRectangle(sf::Color color, float radius);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		RoundedRectangle* copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, RoundedRectangle *&roundedRectangle);
	
	template<>
	bool determine<RoundedRectangle>(const YAML::Node &node);
}
