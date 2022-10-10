#pragma once
#include "../layer.hpp"
#include "../../../../layout/object/layoutWithObject.hpp"

namespace ui
{
	class MakePermeable : public Layer, public LayoutWithObject
	{
	public:
		MakePermeable( IScalable* object, sf::Vector2f minSize );

		void resize(sf::Vector2f size, sf::Vector2f position) override;

		bool updateInteractions(sf::Vector2f mousePosition) override;

		MakePermeable *copy();
	};
	
	bool convertPointer(const YAML::Node &node, MakePermeable *&makePermeable);
}