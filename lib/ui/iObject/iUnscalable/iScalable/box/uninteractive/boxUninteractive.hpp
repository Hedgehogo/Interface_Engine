#pragma once

#include "../../uninteractive/uninteractive.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"
#include "../box.hpp"

namespace ui {
	class BoxUninteractive : public IUninteractive, public LayoutWithObject, public Box {
	public:
		BoxUninteractive(IScalable *object, sf::Vector2f minSize = {0, 0});
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		BoxUninteractive *copy() override;
	};
	
	bool convertPointer(const YAML::Node &node, BoxUninteractive *&boxUninteractive);
}