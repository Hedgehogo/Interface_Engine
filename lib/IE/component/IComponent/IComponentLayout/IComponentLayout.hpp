#pragma once

#include "IE/layout/ILayout/ILayout.hpp"
#include "../IComponent.hpp"

namespace ie {
	class IComponentLayout : public virtual ILayout, public virtual IComponent {
	public:
		struct Make : public virtual IComponent::Make {
			virtual IComponentLayout* make(InitInfo init_info) = 0;
		};
		
		void set_position(sf::Vector2f position) override;
		
		void move(sf::Vector2f position) override;
		
		void set_size(sf::Vector2f size) override;
		
		sf::Vector2f get_area_position() const override;
		
		sf::Vector2f get_area_size() const override;
		
		bool in_area(sf::Vector2f point_position) const override;
	};
}
