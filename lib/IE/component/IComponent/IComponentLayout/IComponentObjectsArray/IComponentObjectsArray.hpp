#pragma once

#include "../IComponentLayout.hpp"
#include "IE/layout/ILayout/ILayoutObjectsArray/ILayoutObjectsArray.hpp"

namespace ie {
	class IComponentObjectsArray : public virtual IComponentLayout, public virtual ILayoutObjectsArray {
	public:
		struct Make : public virtual IComponentLayout::Make {
			virtual IComponentObjectsArray* make(InitInfo init_info) = 0;
		};
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	};
}
