#pragma once

#include "IE/layout/ILayout/ILayout.hpp"
#include "../IComponent.hpp"

namespace ie {
	class IComponentLayout : public virtual ILayout, public virtual IComponent {
	public:
		struct Make : public virtual IComponent::Make {
			virtual auto make(InitInfo init_info) -> IComponentLayout* = 0;
		};
		
		auto set_position(sf::Vector2f position) -> void override;
		
		auto move(sf::Vector2f position) -> void override;
		
		auto set_size(sf::Vector2f size) -> void override;
		
		auto get_area_position() const -> sf::Vector2f override;
		
		auto get_area_size() const -> sf::Vector2f override;
		
		auto in_area(sf::Vector2f point_position) const -> bool override;
	};
}
