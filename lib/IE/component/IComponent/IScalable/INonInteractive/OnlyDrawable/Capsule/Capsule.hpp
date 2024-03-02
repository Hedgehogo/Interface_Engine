#pragma once

#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "../OnlyDrawable.hpp"
#include "../../INonInteractiveLayout/INonInteractiveLayout.hpp"

namespace ie {
	class Capsule : public OnlyDrawable, public virtual INonInteractiveLayout {
	public:
		struct Make : public virtual INonInteractiveLayout::Make {
			sf::Color color;
			
			Make(sf::Color color);
			
			auto make(InitInfo init_info) -> Capsule* override;
		};
		
		Capsule(Make&& make, InitInfo init_info);
		
		Capsule(sf::Color color);
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
	protected:
		auto layout_get_data() -> LayoutData& override;
		
		auto layout_get_data() const -> LayoutData const& override;
		
		LayoutData layout_;
		sf::RectangleShape rectangle_;
		sf::CircleShape circle_;
	};
}

template<>
struct ieml::Decode<char, ie::Capsule::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::Capsule::Make>;
};
