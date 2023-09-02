#include "WhileSwitchTabsAction.hpp"

namespace ie {
	WhileSwitchTabsAction::Make::Make(int step) : step(step) {
	}
	
	WhileSwitchTabsAction* WhileSwitchTabsAction::Make::make(BasicActionInitInfo<BoxSwitchTabs&> initInfo) {
		return new WhileSwitchTabsAction{std::move(*this), initInfo};
	}
	
	WhileSwitchTabsAction::WhileSwitchTabsAction(Make&& make, BasicActionInitInfo<BoxSwitchTabs&> initInfo) :
		BaseSwitchTabsAction(initInfo), size(box->getArraySize()), value(box->getValue()), step(make.step) {
	}
	
	WhileSwitchTabsAction::WhileSwitchTabsAction(int step) :
		size(0), value(nullptr), step(step) {
	}
	
	void WhileSwitchTabsAction::init(BasicActionInitInfo<BoxSwitchTabs&> initInfo) {
		BaseSwitchTabsAction::init(initInfo);
		size = box->getArraySize();
		value = box->getValue();
	}
	
	void WhileSwitchTabsAction::startPressed() {
	}
	
	void WhileSwitchTabsAction::stopPressed() {
		int indexValue = value->getValue();
		indexValue += step;
		indexValue = (((indexValue % size) + size) % size);
		value->setValue(indexValue);
	}
	
	void WhileSwitchTabsAction::whilePressed() {
	}
	
	void WhileSwitchTabsAction::whileNotPressed() {
	}
	
	WhileSwitchTabsAction* WhileSwitchTabsAction::copy() {
		return new WhileSwitchTabsAction{*this};
	}
	
	bool DecodePointer<WhileSwitchTabsAction>::decodePointer(const YAML::Node&, WhileSwitchTabsAction*& whileChangingObjectsAction) {
		whileChangingObjectsAction = new WhileSwitchTabsAction{};
		return true;
	}
}