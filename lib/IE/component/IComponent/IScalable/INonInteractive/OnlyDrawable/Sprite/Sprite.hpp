#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/ieml/shortcuts/shortcuts.hpp"
#include "../OnlyDrawable.hpp"

namespace ie {
	class Sprite : public OnlyDrawable {
	public:
		struct Make : public virtual INonInteractive::Make {
			sf::Texture& texture;
			sf::IntRect rect;
			sf::Vector2f min_size;
			
			Make(sf::Texture& texture, sf::IntRect rect, sf::Vector2f min_size = {});
			
			Make(sf::Texture& texture, sf::Vector2f min_size = {});
			
			auto make(InitInfo init_info) -> Sprite* override;
		};
		
		Sprite(Make&& make, InitInfo init_info);
		
		Sprite(sf::Texture& texture, sf::IntRect rect, sf::Vector2f min_size = {});
		
		Sprite(sf::Texture& texture, sf::Vector2f min_size = {});
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_area_position() const -> sf::Vector2f override;
		
		auto get_area_size() const -> sf::Vector2f override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
	protected:
		sf::Sprite sprite_;
		sf::Vector2f minimum_size_;
	};
	
	template<>
	struct Determine<Sprite::Make> {
		static auto determine(ieml::Node const& node) -> bool;
	};
}

template<>
struct ieml::Decode<char, ie::Sprite::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Sprite::Make>;
};
