#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/ieml/shortcuts/shortcuts.hpp"
#include "../OnlyDrawable.hpp"

namespace ie {
	class Sprite : public OnlyDrawable {
	public:
		struct Make : public virtual IUninteractive::Make {
			sf::Texture& texture;
			sf::IntRect rect;
			sf::Vector2f min_size;
			
			Make(sf::Texture& texture, sf::IntRect rect, sf::Vector2f min_size = {});
			
			Make(sf::Texture& texture, sf::Vector2f min_size = {});
			
			Sprite* make(InitInfo init_info) override;
		};
		
		Sprite(Make&& make, InitInfo init_info);
		
		Sprite(sf::Texture& texture, sf::IntRect rect, sf::Vector2f min_size = {});
		
		Sprite(sf::Texture& texture, sf::Vector2f min_size = {});
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		Sprite* copy() override;
	
	protected:
		sf::Sprite sprite;
		sf::Vector2f minimum_size;
	};
	
	template<>
	struct Determine<Sprite::Make> {
		static bool determine(ieml::Node const& node);
	};
}

template<>
struct ieml::Decode<char, ie::Sprite::Make> {
	static orl::Option<ie::Sprite::Make> decode(ieml::Node const& node);
};
