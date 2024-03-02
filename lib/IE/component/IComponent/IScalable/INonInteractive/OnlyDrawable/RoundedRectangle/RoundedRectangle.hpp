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
			
			auto make(InitInfo init_info) -> RoundedRectangle* override;
		};
		
		RoundedRectangle(Make&& make, InitInfo init_info);
		
		RoundedRectangle(sf::Color color, float radius);
		
		auto draw() -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
	protected:
		auto layout_get_data() -> LayoutData& override;
		
		auto layout_get_data() const -> LayoutData const& override;
		
		LayoutData layout_;
		sf::RectangleShape horizontal_rectangle_;
		sf::RectangleShape vertical_rectangle_;
		sf::CircleShape circle_;
		float radius_;
	};
	
	template<>
	struct Determine<RoundedRectangle::Make> {
		static auto determine(ieml::Node const& node) -> bool;
	};
}

template<>
struct ieml::Decode<char, ie::RoundedRectangle::Make> {
	static auto decode(ieml::Node const& node) -> orl::Option<ie::RoundedRectangle::Make>;
};
