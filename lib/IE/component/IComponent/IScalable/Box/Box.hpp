#pragma once

#include "../IScalable.hpp"
#include "../IScalableLayout/IScalableLayout.hpp"

namespace ie {
	class Box : public virtual IScalableLayout {
	public:
		struct Make : public virtual IScalableLayout::Make {
			virtual auto make(InitInfo init_info) -> Box* = 0;
		};
		
		explicit Box(sf::Vector2f min_size, sf::Vector2f size = {0.0f, 0.0f});
		
	protected:
		auto layout_get_data() -> LayoutData& override;
		
		auto layout_get_data() const -> LayoutData const& override;
		
		LayoutData layout_;
		sf::Vector2f minimum_size_;
	};
}

