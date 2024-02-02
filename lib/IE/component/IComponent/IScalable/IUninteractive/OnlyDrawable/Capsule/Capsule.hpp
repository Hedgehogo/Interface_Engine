#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../OnlyDrawable.hpp"
#include "../../IUninteractiveLayout/IUninteractiveLayout.hpp"

namespace ie {
	class Capsule : public OnlyDrawable, public virtual IUninteractiveLayout {
	public:
		struct Make : public virtual IUninteractiveLayout::Make {
			sf::Color color;
			
			Make(sf::Color color);
			
			Capsule* make(InitInfo init_info) override;
		};
		
		Capsule(Make&& make, InitInfo init_info);
		
		Capsule(sf::Color color);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
	protected:
		LayoutData& layout_get_data() override;
		
		const LayoutData& layout_get_data() const override;
		
		LayoutData layout_;
		sf::RectangleShape rectangle_;
		sf::CircleShape circle_;
	};
}

template<>
struct ieml::Decode<char, ie::Capsule::Make> {
	static orl::Option<ie::Capsule::Make> decode(ieml::Node const& node);
};
