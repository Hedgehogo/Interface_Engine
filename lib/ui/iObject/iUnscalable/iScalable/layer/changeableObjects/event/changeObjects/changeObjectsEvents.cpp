#include "changeObjectsEvents.hpp"

namespace ui
{
	void ChangeObjectsEvent::startPressed()
	{
		object->setCurrent(index);
	}

	void ChangeObjectsEvent::stopPressed() {}

	void ChangeObjectsEvent::whilePressed() {}

	void ChangeObjectsEvent::whileNotPressed() {}

	ChangeObjectsEvent::ChangeObjectsEvent(uint index, LayerWithChangeableObjects *objects ) : index( index ), ChangeableObjectsEvent( objects ) {}

	ChangeObjectsEvent *ChangeObjectsEvent::copy()
	{
		return new ChangeObjectsEvent { index, object };
	}

	ChangeObjectsEvent *ChangeObjectsEvent::createFromYaml(const YAML::Node &node)
	{
		uint index;
		LayerWithChangeableObjects *object = nullptr;
		node["index"] >> index;

		if (node["object"]) node["object"] >> object;

		return new ChangeObjectsEvent { index, object };
	}
} // ui