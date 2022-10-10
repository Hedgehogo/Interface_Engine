#include "makePermeable.hpp"

namespace ui {
	MakePermeable::MakePermeable(IScalable *object, sf::Vector2f minSize) : Layer(minSize), LayoutWithObject(object) {}

	void MakePermeable::resize(sf::Vector2f size, sf::Vector2f position)
	{
		LayoutWithObject::resize( size, position );
	}

	bool MakePermeable::updateInteractions(sf::Vector2f mousePosition)
	{
		object->updateInteractions( mousePosition );
		return false;
	}

	MakePermeable *MakePermeable::copy()
	{
		MakePermeable* makePermeable { new MakePermeable{ object->copy(), minimumSize } };
		Layer::copy(makePermeable);
		return makePermeable;
	}

	bool convertPointer(const YAML::Node &node, MakePermeable *&makePermeable)
	{
		IScalable *object;
		sf::Vector2f minSize {};
		node["object"] >> object;
		if ( node["min-size"] ) node["min-size"] >> minSize;

		return new MakePermeable(object, minSize);
	}
}