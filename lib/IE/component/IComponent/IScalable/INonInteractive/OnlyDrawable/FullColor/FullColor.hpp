#pragma once

#include "../OnlyDrawable.hpp"
#include "IE/ieml/shortcuts/shortcuts.hpp"

namespace ie {
	class FullColor : public OnlyDrawable {
	public:
		struct Make : public virtual INonInteractive::Make {
			sf::Color color;
			sf::Vector2f normal_size = {};
			
			Make(sf::Color color, sf::Vector2f normal_size = {0, 0});
			
			FullColor* make(InitInfo init_info) override;
		};
		
		FullColor(Make&& make, InitInfo init_info);
		
		explicit FullColor(sf::Color color, sf::Vector2f normal_size = {0, 0});
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
	protected:
		sf::RectangleShape rectangle_;
		sf::Vector2f normal_size_;
	};
	
	template<>
	struct Determine<FullColor::Make> {
		static bool determine(ieml::Node const& node);
	};
}

template<>
struct ieml::Decode<char, ie::FullColor::Make> {
	static orl::Option<ie::FullColor::Make> decode(ieml::Node const& node);
};
