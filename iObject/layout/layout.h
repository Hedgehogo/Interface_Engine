#pragma once
#include "../iObject.h"

namespace ui {
	class Layout : public virtual IObject {
	protected:
		sf::Vector2f position;
		sf::Vector2f size;
		
		void copy(Layout* layout);
		
	public:
		explicit Layout(sf::Vector2f size = {});
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getPosition() override;
		
		sf::Vector2f getAreaSize() override;
	};
}
