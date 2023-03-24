#pragma once

#include "../box.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"

namespace ui {
	class BoxMakePermeable : public Box, public LayoutWithObject {
	public:
		BoxMakePermeable(IScalable *object, sf::Vector2f minSize);
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BoxMakePermeable *copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, BoxMakePermeable *&boxMakePermeable);
}