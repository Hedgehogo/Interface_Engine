#pragma once

#include "../box.hpp"
#include "../../../../layout/twoObjects/layoutWithTwoObjects.hpp"

namespace ui {
	class BoxWithAlternativeObject : public Box, public LayoutWithTwoObjects {
	public:
		BoxWithAlternativeObject(IScalable *topObject, IScalable *bottomObject, sf::Vector2f minSize = {});
		
		bool updateInteractions(sf::Vector2f mousePosition) override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		BoxWithAlternativeObject *copy() override;
	};
	
	
	template<>
	struct DecodePointer<BoxWithAlternativeObject> {
		static bool decodePointer(const YAML::Node &node, BoxWithAlternativeObject *&boxWithAlternativeObject);
	};
	
	using BoxWAObject = BoxWithAlternativeObject;
	using BWAO = BoxWithAlternativeObject;
}
