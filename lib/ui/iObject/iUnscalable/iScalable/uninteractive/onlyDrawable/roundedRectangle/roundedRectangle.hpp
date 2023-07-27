#pragma once

#include "../onlyDrawable.hpp"
#include "../../../../../layout/layout.hpp"

namespace ui {
	class RoundedRectangle : public OnlyDrawable, public Layout {
	public:
		RoundedRectangle(sf::Color color, float radius);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		RoundedRectangle* copy() override;
	
	protected:
		sf::RectangleShape horizontalRectangle;
		sf::RectangleShape verticalRectangle;
		sf::CircleShape circle;
		float radius;
	};
	
	template<>
	struct DecodePointer<RoundedRectangle> {
		static bool decodePointer(const YAML::Node& node, RoundedRectangle*& roundedRectangle);
	};
	
	template<>
	bool determine<RoundedRectangle>(const YAML::Node& node);
}
