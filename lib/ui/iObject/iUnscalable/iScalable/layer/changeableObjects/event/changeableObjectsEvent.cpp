#include "changeableObjectsEvent.hpp"

namespace ui
{
	ChangeableObjectsEvent::ChangeableObjectsEvent(LayerWithChangeableObjects *objects) : object(objects) {}

	void ChangeableObjectsEvent::setObject(LayerWithChangeableObjects *object)
	{
		this->object = object;
	}

	LayerWithChangeableObjects *ChangeableObjectsEvent::getObject()
	{
		return object;
	}
} // ui