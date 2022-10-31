#pragma once

#include "../LayerWithChangeableObjects.hpp"
#include "../../../../../../interaction/event/key/simple/keyEventSimple.hpp"

namespace ui
{
	class ChangeableObjectsEvent : public KeyEvent_Simple
	{
	protected:
		LayerWithChangeableObjects *object;

	public:
		ChangeableObjectsEvent(LayerWithChangeableObjects *objects = nullptr );

		virtual void setObject(LayerWithChangeableObjects *object);

		virtual LayerWithChangeableObjects* getObject();
	};
} // ui
