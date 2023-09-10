#pragma once

#include "../IScalable.hpp"
#include "../IScalableLayout/IScalableLayout.hpp"

namespace ie {
	class Box : public virtual IScalableLayout {
	public:
		struct Make : public virtual IScalableLayout::Make {
			virtual Box* make(InitInfo initInfo) = 0;
		};
		
		explicit Box(sf::Vector2f minSize, sf::Vector2f size = {0.0f, 0.0f});
		
		Box* copy() override = 0;
	
	protected:
		LayoutData& layoutGetData() override;
		
		const LayoutData& layoutGetData() const override;
		
		LayoutData layout;
		sf::Vector2f minimumSize;
	};
}

