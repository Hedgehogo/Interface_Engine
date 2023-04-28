#pragma once

#include "../boxWithChangeableObjects.hpp"
#include "../../../../../../interaction/event/key/simple/keyEventSimple.hpp"

namespace ui {
	class ChangeableObjectsEvent : public KeyEvent_Simple {
	protected:
		BoxWithChangeableObjects* object;
	
	public:
		ChangeableObjectsEvent(BoxWithChangeableObjects* objects = nullptr);
		
		virtual void setObject(BoxWithChangeableObjects* object);
		
		virtual BoxWithChangeableObjects* getObject();
	};
}
