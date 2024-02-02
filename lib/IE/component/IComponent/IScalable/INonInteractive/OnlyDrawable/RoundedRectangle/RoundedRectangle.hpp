#pragma once

#include "../OnlyDrawable.hpp"
#include "../../INonInteractiveLayout/INonInteractiveLayout.hpp"
#include "IE/ieml/shortcuts/shortcuts.hpp"

namespace ie {
	class RoundedRectangle : public OnlyDrawable, public virtual INonInteractiveLayout {
	public:
		struct Make : public virtual INonInteractiveLayout::Make {
			sf::Color color;
			float radius;
			
			Make(sf::Color color, float radius);
			
			RoundedRectangle* make(InitInfo init_info) override;
		};
		
		RoundedRectangle(Make&& make, InitInfo init_info);
		
		RoundedRectangle(sf::Color color, float radius);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
	protected:
		LayoutData& layout_get_data() override;
		
		const LayoutData& layout_get_data() const override;
		
		LayoutData layout_;
		sf::RectangleShape horizontal_rectangle_;
		sf::RectangleShape vertical_rectangle_;
		sf::CircleShape circle_;
		float radius_;
	};
	
	template<>
	struct Determine<RoundedRectangle::Make> {
		static bool determine(ieml::Node const& node);
	};
}

template<>
struct ieml::Decode<char, ie::RoundedRectangle::Make> {
	static orl::Option<ie::RoundedRectangle::Make> decode(ieml::Node const& node);
};
