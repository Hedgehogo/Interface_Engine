#include "whileChangingObjectsEvent.hpp"

namespace ui
{
	void WhileChangingObjectsEvent::startPressed() {}

	void WhileChangingObjectsEvent::stopPressed() {
		int indexValue = index->getValue();
		indexValue += offset;
		indexValue = (((indexValue % objectsSize) + objectsSize) % objectsSize);
		index->setValue(indexValue);
	}

	void WhileChangingObjectsEvent::whilePressed() {}

	void WhileChangingObjectsEvent::whileNotPressed() {}

	WhileChangingObjectsEvent::WhileChangingObjectsEvent(LayerWithChangeableObjects *objects, int offset ) :
	index(object->getValue()), objectsSize( objects->getArraySize()), ChangeableObjectsEvent( objects ), offset( offset) {}

	WhileChangingObjectsEvent *WhileChangingObjectsEvent::copy()
	{
		return new WhileChangingObjectsEvent { object };
	}

	WhileChangingObjectsEvent *WhileChangingObjectsEvent::createFromYaml(const YAML::Node &node)
	{
		LayerWithChangeableObjects *object = nullptr;

		if (node["object"]) node["object"] >> object;

		return new WhileChangingObjectsEvent { object };
	}
} // ui