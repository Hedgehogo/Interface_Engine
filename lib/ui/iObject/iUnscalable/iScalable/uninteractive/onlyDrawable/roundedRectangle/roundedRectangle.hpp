#pragma once

#include "../onlyDrawable.hpp"
#include "ui/iObject/iLayout/iLayout.hpp"

namespace ui {
	class RoundedRectangle : public OnlyDrawable, public ILayout {
	public:
		RoundedRectangle(sf::Color color, float radius);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		LayoutData& getLayoutData() override;
		
		const LayoutData& getLayoutData() const override;
		
		RoundedRectangle* copy() override;
	
	protected:
		LayoutData layout;
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
