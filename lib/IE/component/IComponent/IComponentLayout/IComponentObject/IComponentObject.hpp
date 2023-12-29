#pragma once

#include "../IComponentLayout.hpp"
#include "IE/layout/ILayout/ILayoutObject/ILayoutObject.hpp"

namespace ie {
	class IComponentObject : public virtual IComponentLayout, public virtual ILayoutObject {
	public:
		struct Make : public virtual IComponentLayout::Make {
			virtual IComponentObject* make(InitInfo init_info) = 0;
		};
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool update_interactions(sf::Vector2f mouse_position) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	};
}
