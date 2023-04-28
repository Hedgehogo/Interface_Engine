#include "changeableObjectsEvent.hpp"

namespace ui {
	ChangeableObjectsEvent::ChangeableObjectsEvent(BoxWithChangeableObjects* objects) : object(objects) {
	}
	
	void ChangeableObjectsEvent::setObject(BoxWithChangeableObjects* object) {
		this->object = object;
	}
	
	BoxWithChangeableObjects* ChangeableObjectsEvent::getObject() {
		return object;
	}
}