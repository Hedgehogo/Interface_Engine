#pragma once

#include "../onlyDrawable.hpp"
#include "IE/iObject/iLayout/iLayout.hpp"

namespace ui {
	class Capsule : public OnlyDrawable, public ILayout {
	public:
		struct Make : public IUninteractive::Make, public ILayout::Make {
			sf::Color color;
			
			Make(sf::Color color);
			
			Capsule* make(InitInfo initInfo) override;
		};
		
		Capsule(Make&& make, InitInfo initInfo);
		
		Capsule(sf::Color color);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() const override;
		
		sf::Vector2f getNormalSize() const override;
		
		Capsule* copy() override;
	
	protected:
		LayoutData& layoutGetData() override;
		
		const LayoutData& layoutGetData() const override;
		
		LayoutData layout;
		sf::RectangleShape rectangle;
		sf::CircleShape circle;
	};
	
	template<>
	struct DecodePointer<Capsule> {
		static bool decodePointer(const YAML::Node& node, Capsule*& capsule);
	};
}
