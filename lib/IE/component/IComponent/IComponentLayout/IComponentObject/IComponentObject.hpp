#pragma once

#include "../IComponentLayout.hpp"
#include "IE/layout/ILayout/ILayoutObject/ILayoutObject.hpp"

namespace ie {
	class IComponentObject : public virtual IComponentLayout, public virtual ILayoutObject {
	public:
		struct Make : public virtual IComponentLayout::Make {
			virtual auto make(InitInfo init_info) -> IComponentObject* = 0;
		};
		
		auto set_position(sf::Vector2f position) -> void override;
		
		auto move(sf::Vector2f offset) -> void override;
		
		auto set_size(sf::Vector2f size) -> void override;
		
		auto resize(sf::Vector2f size, sf::Vector2f position) -> void override;
		
		auto update_interactions(Event event) -> bool override;
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	};
}
