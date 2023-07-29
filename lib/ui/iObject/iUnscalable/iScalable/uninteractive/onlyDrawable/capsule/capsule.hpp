#pragma once

#include "../onlyDrawable.hpp"
#include "ui/iObject/iLayout/iLayout.hpp"

namespace ui {
	class Capsule : public OnlyDrawable, public ILayout {
	public:
		Capsule(sf::Color color);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		LayoutData& getLayoutData() override;
		
		const LayoutData& getLayoutData() const override;
		
		Capsule* copy() override;
	
	protected:
		LayoutData layout;
		sf::RectangleShape rectangle;
		sf::CircleShape circle;
	};
	
	template<>
	struct DecodePointer<Capsule> {
		static bool decodePointer(const YAML::Node& node, Capsule*& capsule);
	};
}
