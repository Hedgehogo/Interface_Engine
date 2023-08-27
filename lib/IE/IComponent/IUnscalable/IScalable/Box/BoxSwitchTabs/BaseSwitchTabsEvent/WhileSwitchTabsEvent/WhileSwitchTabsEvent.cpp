#include "WhileSwitchTabsEvent.hpp"

namespace ie {
	void WhileSwitchTabsEvent::startPressed() {
	}
	
	void WhileSwitchTabsEvent::stopPressed() {
		int indexValue = index->getValue();
		indexValue += offset;
		indexValue = (((indexValue % objectsSize) + objectsSize) % objectsSize);
		index->setValue(indexValue);
	}
	
	void WhileSwitchTabsEvent::whilePressed() {
	}
	
	void WhileSwitchTabsEvent::whileNotPressed() {
	}
	
	WhileSwitchTabsEvent::WhileSwitchTabsEvent(BoxSwitchTabs* objects, int offset) :
		BaseSwitchTabsEvent(objects), objectsSize(objects->getArraySize()), index(object->getValue()), offset(offset) {
	}
	
	WhileSwitchTabsEvent* WhileSwitchTabsEvent::copy() {
		return new WhileSwitchTabsEvent{*this};
	}
	
	bool DecodePointer<WhileSwitchTabsEvent>::decodePointer(const YAML::Node& node, WhileSwitchTabsEvent*& whileChangingObjectsEvent) {
		whileChangingObjectsEvent = new WhileSwitchTabsEvent{
			convDef<BoxSwitchTabs*>(node["object"], nullptr)
		};
		return true;
	}
}