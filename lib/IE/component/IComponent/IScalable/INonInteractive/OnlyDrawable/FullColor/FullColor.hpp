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
			
			auto make(InitInfo init_info) -> FullColor* override;
		};
		
		FullColor(Make&& make, InitInfo init_info);
		
		explicit FullColor(sf::Color color, sf::Vector2f normal_size = {0, 0});
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_area_position() const -> sf::Vector2f override;
		
		auto get_area_size() const -> sf::Vector2f override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
	protected:
		sf::RectangleShape rectangle_;
		sf::Vector2f normal_size_;
	};
	
	template<>
	struct Determine<FullColor::Make> {
		static auto determine(ieml::Node const& node) -> bool;
	};
}

template<>
struct ieml::Decode<char, ie::FullColor::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::FullColor::Make>;
};
