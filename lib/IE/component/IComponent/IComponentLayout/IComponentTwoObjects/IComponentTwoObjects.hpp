#pragma once

#include "../IComponentObjectsArray/IComponentObjectsArray.hpp"
#include "IE/layout/ILayout/ILayoutTwoObjects/ILayoutTwoObjects.hpp"

namespace ie {
	class IComponentTwoObjects : public virtual IComponentObjectsArray, public virtual ILayoutTwoObjects{
	public:
		struct Make : public virtual IComponentObjectsArray::Make {
			virtual IComponentTwoObjects* make(InitInfo init_info) = 0;
		};
		
		sf::Vector2f get_min_size() const override;
		
		sf::Vector2f get_normal_size() const override;
		
		void draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) override;
	};
}
