#pragma once

#include "../LayerWithChangeableObjects.hpp"
#include "../../../../../../interaction/event/button/simple/buttonEventSimple.hpp"

namespace ui
{
	class ChangeableObjectsEvent : public ButtonEvent_Simple
	{
	protected:
		LayerWithChangeableObjects *object;

	public:
		ChangeableObjectsEvent(LayerWithChangeableObjects *objects = nullptr );

		virtual void setObject(LayerWithChangeableObjects *object);

		virtual LayerWithChangeableObjects* getObject();
	};
} // ui
