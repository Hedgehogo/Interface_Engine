#include "whileChangingObjectsEvent.hpp"

namespace ui
{
	void WhileChangingObjectsEvent::startPressed()
	{
		index += offset;
		if (index >= objectsSize) index = (index - objectsSize) % objectsSize;
		else if (index < 0) index = (objectsSize - ((-index) % objectsSize)) - 1;
		object->setCurrent(index);
	}

	void WhileChangingObjectsEvent::stopPressed() {}

	void WhileChangingObjectsEvent::whilePressed() {}

	void WhileChangingObjectsEvent::whileNotPressed() {}

	WhileChangingObjectsEvent::WhileChangingObjectsEvent(LayerWithChangeableObjects *objects, int offset ) : index( object->getIndex()), objectsSize( objects->getArraySize()), ChangeableObjectsEvent( objects ), offset( offset) {}

	WhileChangingObjectsEvent *WhileChangingObjectsEvent::copy()
	{
		return new WhileChangingObjectsEvent { object };
	}

	WhileChangingObjectsEvent *WhileChangingObjectsEvent::createFromYaml(const YAML::Node &node)
	{
		uint index;
		LayerWithChangeableObjects *object = nullptr;
		node["index"] >> index;

		if (node["object"]) node["object"] >> object;

		return new WhileChangingObjectsEvent { object };
	}
} // ui