#pragma once

#include "../boxWithChangeableObjects.hpp"
#include "../../../../../../Interaction/IEvent/KeyEvent/BaseKeyEvent/BaseKeyEvent.hpp"

namespace ui {
	class ChangeableObjectsEvent : public BaseKeyEvent {
	public:
		ChangeableObjectsEvent(BoxWithChangeableObjects* objects = nullptr);
		
		virtual void setObject(BoxWithChangeableObjects* object);
		
		virtual BoxWithChangeableObjects* getObject();
	
	protected:
		BoxWithChangeableObjects* object;
	};
}
