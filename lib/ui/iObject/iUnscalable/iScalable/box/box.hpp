#pragma once

#include "../iScalable.hpp"
#include "ui/iObject/iLayout/iLayout.hpp"

namespace ui {
	class Box : public virtual IScalable, public virtual ILayout {
	public:
		struct Make : public virtual IScalable::Make, public virtual ILayout::Make {
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

