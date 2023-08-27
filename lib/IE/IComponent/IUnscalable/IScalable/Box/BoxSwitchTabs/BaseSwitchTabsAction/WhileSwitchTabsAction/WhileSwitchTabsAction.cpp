#include "WhileSwitchTabsAction.hpp"

namespace ie {
	void WhileSwitchTabsAction::startPressed() {
	}
	
	void WhileSwitchTabsAction::stopPressed() {
		int indexValue = index->getValue();
		indexValue += offset;
		indexValue = (((indexValue % objectsSize) + objectsSize) % objectsSize);
		index->setValue(indexValue);
	}
	
	void WhileSwitchTabsAction::whilePressed() {
	}
	
	void WhileSwitchTabsAction::whileNotPressed() {
	}
	
	WhileSwitchTabsAction::WhileSwitchTabsAction(BoxSwitchTabs* objects, int offset) :
		BaseSwitchTabsAction(objects), objectsSize(objects->getArraySize()), index(object->getValue()), offset(offset) {
	}
	
	WhileSwitchTabsAction* WhileSwitchTabsAction::copy() {
		return new WhileSwitchTabsAction{*this};
	}
	
	bool DecodePointer<WhileSwitchTabsAction>::decodePointer(const YAML::Node& node, WhileSwitchTabsAction*& whileChangingObjectsAction) {
		whileChangingObjectsAction = new WhileSwitchTabsAction{
			convDef<BoxSwitchTabs*>(node["object"], nullptr)
		};
		return true;
	}
}