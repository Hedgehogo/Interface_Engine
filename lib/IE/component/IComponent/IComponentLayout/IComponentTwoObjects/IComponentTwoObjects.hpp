#pragma once

#include "../IComponentObjectsArray/IComponentObjectsArray.hpp"
#include "IE/layout/ILayout/ILayoutTwoObjects/ILayoutTwoObjects.hpp"

namespace ie {
	class IComponentTwoObjects : public virtual IComponentObjectsArray, public virtual ILayoutTwoObjects{
	public:
		struct Make : public virtual IComponentObjectsArray::Make {
			virtual auto make(InitInfo init_info) -> IComponentTwoObjects* = 0;
		};
		
		auto get_min_size() const -> sf::Vector2f override;
		
		auto get_normal_size() const -> sf::Vector2f override;
		
		auto draw_debug(sf::RenderTarget& render_target, int indent, int indent_addition, size_t hue, size_t hue_offset) -> void override;
	};
}
