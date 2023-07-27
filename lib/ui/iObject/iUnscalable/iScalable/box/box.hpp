#pragma once

#include "../iScalable.hpp"
#include "../../../layout/layout.hpp"

namespace ui {
	class Box : public virtual IScalable, public virtual Layout {
	protected:
		void copy(Box* box);
	
	public:
		explicit Box(sf::Vector2f minSize, sf::Vector2f size = {0.0f, 0.0f});
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		Box* copy() override = 0;
	
	protected:
		sf::Vector2f minimumSize;
	};
}

