#pragma once

#include "../IScalable.hpp"
#include "../IScalableLayout/IScalableLayout.hpp"

namespace ie {
	class Box : public virtual IScalableLayout {
	public:
		struct Make : public virtual IScalableLayout::Make {
			virtual Box* make(InitInfo init_info) = 0;
		};
		
		explicit Box(sf::Vector2f min_size, sf::Vector2f size = {0.0f, 0.0f});
		
		Box* copy() override = 0;
	
	protected:
		LayoutData& layout_get_data() override;
		
		const LayoutData& layout_get_data() const override;
		
		LayoutData layout_;
		sf::Vector2f minimum_size_;
	};
}

