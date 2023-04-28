#include "whileChangingObjectsEvent.hpp"

namespace ui {
	void WhileChangingObjectsEvent::startPressed() {
	}
	
	void WhileChangingObjectsEvent::stopPressed() {
		int indexValue = index->getValue();
		indexValue += offset;
		indexValue = (((indexValue % objectsSize) + objectsSize) % objectsSize);
		index->setValue(indexValue);
	}
	
	void WhileChangingObjectsEvent::whilePressed() {
	}
	
	void WhileChangingObjectsEvent::whileNotPressed() {
	}
	
	WhileChangingObjectsEvent::WhileChangingObjectsEvent(BoxWithChangeableObjects* objects, int offset) :
		index(object->getValue()), objectsSize(objects->getArraySize()), ChangeableObjectsEvent(objects), offset(offset) {
	}
	
	WhileChangingObjectsEvent* WhileChangingObjectsEvent::copy() {
		return new WhileChangingObjectsEvent{object};
	}
	
	bool convertPointer(const YAML::Node &node, WhileChangingObjectsEvent *&whileChangingObjectsEvent) {
		BoxWithChangeableObjects* object = nullptr;
		
		if(node["object"])
			node["object"] >> object;
		
		{
			whileChangingObjectsEvent = new WhileChangingObjectsEvent{object};
			return true;
		}
	}
	
	bool DecodePointer<WhileChangingObjectsEvent>::decodePointer(const YAML::Node &node, WhileChangingObjectsEvent *&whileChangingObjectsEvent) {
		BoxWithChangeableObjects* object = nullptr;
		
		if(node["object"])
			node["object"] >> object;
		
		{
			whileChangingObjectsEvent = new WhileChangingObjectsEvent{object};
			return true;
		}
	}
}